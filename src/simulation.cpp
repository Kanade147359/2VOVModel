#include "simulation.hpp"
#include <iostream>
#include <vector>
#include <cmath>
#include <array>
#include <string>
#include <fstream>
#include <queue>
#include <algorithm>

// 角度依存性関数
std::array<double, 2> F(double V, double cos_phi, std::array<double, 2> emn) {
    return {(V * (1 + cos_phi)) * emn[0], (V * (1 + cos_phi)) * emn[1]};
}

// 力関数
double V(double r, double b, double c) {
    return 0.25 * (std::tanh(2.5*(r - b)) + c);
}

Values find_neighbors(Values& positions, int j, int num, double width, double height){
    std::priority_queue<std::pair<double, int>> max_heap; // 距離
    
    for (int k = 0; k < num; ++k)
    {
        if (k == j) continue; // 自分自身は無視
        double dx = positions[k][0] - positions[j][0];
        double dy = positions[k][1] - positions[j][1];
        if (std::abs(dx) < 1e-6 && std::abs(dy) < 1e-6) continue;
        if (dx < -width/2) dx += width;
        if (dx > width/2) dx -= width;
        if (dy < -height/2) dy += height;
        if (dy > height/2) dy -= height;

        double r_kj = std::sqrt(dx*dx + dy*dy);

        max_heap.push({r_kj, k});

        if (max_heap.size() > 6) {
            max_heap.pop();
        }
    }

        // ヒープから結果を取り出して返す
    Values neighbors;
    while (!max_heap.empty()) {
        neighbors.push_back(positions[max_heap.top().second]);
        max_heap.pop();
    }

    // ヒープの中身は最大値から順に取り出されるので、結果を反転させる
    std::reverse(neighbors.begin(), neighbors.end());
    return neighbors;
}

Values sort_and_select_top_6(const Values& positions, const std::vector<double>& distances) {
    
    std::vector<size_t> indices(distances.size());
    for (size_t i = 0; i < distances.size(); ++i) {
        indices[i] = i;
    }

    std::sort(indices.begin(), indices.end(), [&distances](size_t a, size_t b) {
        return distances[a] < distances[b];
    });

    Values sorted_neighbors;

    for (size_t i = 0; i < 6; ++i) {
        sorted_neighbors.push_back(positions[indices[i]]);
    }

    return sorted_neighbors;
}

void calculate_acceleration(std::array<double, 2> position, std::array<double, 2> velocity, Values neighbors, double a, double b, double c, double &ax, double &ay)
{
    double F_sum_x = 0;
    double F_sum_y = 0;
    for (auto neighbor : neighbors){
        double dx = neighbor[X] - position[X];
        double dy = neighbor[Y] - position[Y];
        double distance = std::sqrt(dx * dx + dy * dy);
        std::array<double, 2> n_kj = {dx / distance, dy / distance};
        double cos_phi = dx / distance;
        F_sum_x += V(distance, b, c) * (1+cos_phi) * n_kj[X];
        F_sum_y += V(distance, b, c) * (1+cos_phi) * n_kj[Y];
    }

    ax = a * ((1.0 + F_sum_x) - velocity[0]);
    ay = a * (F_sum_y - velocity[1]);
}

// 位置と速度の更新関数
void update(Values& positions, 
            Values& velocities, 
            double dt, 
            double a, 
            double b,
            double c,
            int num,
            double width,
            double height
            ) {
    // 速度の更新
    for (int j = 0; j < num; ++j){
        // 近傍粒子の探索 {dx, dy}基準となる粒子との相対距離
        Values neighbors = find_neighbors(positions, j, num, width, height);
        double ax, ay;
        calculate_acceleration(positions[j],velocities[j],neighbors, b, c, a, ax, ay);
        velocities[j][X] += ax * dt;
        velocities[j][Y] += ay * dt;
    }
    // 位置の更新
    for (int i = 0; i < num; ++i){

        // 位置の更新
        positions[i][X] += velocities[i][X] * dt;
        positions[i][Y] += velocities[i][Y] * dt;

        // x軸方向の境界条件
        if (positions[i][X] >= width) positions[i][X] -= width;
        if (positions[i][X] < 0) positions[i][X] += width;

        // y軸方向の境界条件
        if (positions[i][Y] >= height) positions[i][Y] -= height;
        if (positions[i][Y] < 0) positions[i][Y] += height;

        // 境界を超えた場合のエラーチェック
        if (positions[i][X] > width || positions[i][Y] > height || positions[i][X] < 0 || positions[i][Y] < 0)
        {
            std::cerr << "Error: Particle " << i << " exceeded boundaries." << std::endl;
            throw std::out_of_range("Particle exceeded width or height boundary");
        }
        }
}

void run_simulation(Values &positions,
                    Values &velocities,
                    int steps,
                    int num,
                    double dt,
                    double a,
                    double b,
                    double c,
                    double width,
                    double height,
                    std::string filepath){

    std::ofstream ofs_csv_file(filepath);

    if (!ofs_csv_file.is_open()) {
        std::cerr << "Error opening file: " << filepath << std::endl;
        return;
    }

    for (int i = 0; i < steps; ++i){
        update(positions, velocities, dt, a, b, c, num, width, height);

        if (i % 20 == 0) {
            if (ofs_csv_file.is_open()) {
                for (int j = 0; j < num; ++j) {
                    ofs_csv_file << positions[j][X] << "," << positions[j][Y] << std::endl;
                }
            }
        }
    }
}