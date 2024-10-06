#include "simulation.hpp"
#include <iostream>
#include <vector>
#include <cmath>
#include <array>
#include <string>
#include <fstream>
#include <algorithm>

// 角度依存性関数
std::array<double, 2> F(double V, double cos_phi, std::array<double, 2> emn) {
    return {(V * (1 + cos_phi)) * emn[0], (V * (1 + cos_phi)) * emn[1]};
}

// 力関数
double V(double r, double b, double c) {
    return 0.25 * (std::tanh(2.5*(r - b)) + std::tanh(c));
}

std::vector<Neighbor> find_neighbors(Values& positions, int n, int num, double width, double height){
    std::vector<Neighbor> neighbors;
    for (int m = 0; m < num; ++m)
    {
        if (m == n) continue; // 自分自身は無視
        double dx = positions[m][0] - positions[n][0];
        double dy = positions[m][1] - positions[n][1];

        if (dx < -width/2) dx += width;
        if (dx > width/2) dx -= width;
        if (dy < -height/2) dy += height;
        if (dy > height/2) dy -= height;

        double rmn = std::sqrt(std::pow(dx, 2) + std::pow(dy, 2));
        // 距離とインデックスをペアとしてリストに追加
        neighbors.push_back({dx, dy, rmn});
    }
    // 距離に基づいて昇順にソート
    std::sort(neighbors.begin(), neighbors.end(), [](const Neighbor &a, const Neighbor &b)
            { return a.distance < b.distance; });

    neighbors.resize(6);  // ベクトルのサイズを6に絞る

    return neighbors;
}

void calculate_acceleration(std::array<double, 2> velocity, std::vector<Neighbor> neighbors, double a, double b, double c, double &ax, double &ay)
{
    double F_sum_x = 0;
    double F_sum_y = 0;
    for (auto neighbor : neighbors)
    {
        std::array<double, 2> emn = { neighbor.dx/ neighbor.distance, neighbor.dy/ neighbor.distance};
        double cos_phi = neighbor.dx / neighbor.distance;
        F_sum_x += V(neighbor.distance, b, c) * (1+cos_phi) * emn[0];
        F_sum_y += V(neighbor.distance, b, c) * (1+cos_phi) * emn[1];
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
    for (int n = 0; n < num; ++n){
        // 隣接粒子の集合を作成
        std::vector<Neighbor> neighbors = find_neighbors(positions, n, num, width, height);
        double ax, ay;
        calculate_acceleration(velocities[n],neighbors, b, c, a, ax, ay);
        velocities[n][0] += ax * dt;
        velocities[n][1] += ay * dt;
    }
    // 位置の更新
    for (int i = 0; i < num; ++i){

        // 位置の更新
        positions[i][0] += velocities[i][0] * dt;
        positions[i][1] += velocities[i][1] * dt;

        // x軸方向の境界条件
        if (positions[i][0] >= width) positions[i][0] -= width;
        if (positions[i][0] < 0) positions[i][0] += width;

        // y軸方向の境界条件
        if (positions[i][1] >= height) positions[i][1] -= height;
        if (positions[i][1] < 0) positions[i][1] += height;

        // 境界を超えた場合のエラーチェック
        if (positions[i][0] > width || positions[i][1] > height || positions[i][0] < 0 || positions[i][1] < 0)
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
                    ofs_csv_file << positions[j][0] << "," << positions[j][1] << std::endl;
                }
            }
        }
    }
}