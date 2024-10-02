#include "simulation.hpp"
#include <iostream>
#include <vector>
#include <cmath>
#include <array>
#include <string>
#include <fstream>
#include <algorithm>

// 角度依存性関数
double P(double cos_theta) {
    return 0.5 * (1 + cos_theta);
}

// 力関数
double V(double r, double c) {
    return std::tanh(r - c) + std::tanh(c);
}

// 構造体またはペアを使用して、距離と粒子のインデックスを保持
struct Neighbor {
    double distance;
    int index;
};

// 位置と速度の更新関数
void update(Values& positions, 
            Values& velocities, 
            Values& accelerations, 
            double dt, 
            double a, 
            double c,
            int num,
            double width,
            double height) {

    Values new_accelerations(num, {0.0, 0.0});


for (int n = 0; n < num; ++n)
    {
    std::array<double, 2> force_sum = {0.0, 0.0};

    // 隣接粒子の集合を作成
    std::vector<Neighbor> neighbors;

    // 全粒子に対して距離を計算し、最近接粒子リストを作成
    for (int m = 0; m < num; ++m)
    {
        if (n == m) continue;  // 自分自身はスキップ

        double dx = positions[n][0] - positions[m][0];
        double dy = positions[n][1] - positions[m][1];

        if (dx < -width/2) dx += width;
        if (dx > width/2) dx -= width;
        if (dy < -height/2) dy += height;
        if (dy > height/2) dy -= height;

        double rmn = std::sqrt(std::pow(dx, 2) + std::pow(dy, 2));
        // 距離とインデックスをペアとしてリストに追加
        neighbors.push_back({rmn, m});
    }

    // 距離に基づいて昇順にソート
    std::sort(neighbors.begin(), neighbors.end(), [](const Neighbor &a, const Neighbor &b)
                { return a.distance < b.distance; });

    // 6番目までの最近接粒子との相互作用を計算
    for (int i = 0; i < std::min(7, static_cast<int>(neighbors.size())); ++i)
    {
        int m = neighbors[i].index; // 近接粒子のインデックス
        double rmn = neighbors[i].distance;

        if (rmn == 0) continue; // 距離がゼロの粒子は無視

        // 単位ベクトルの計算
        std::array<double, 2> emn = {(positions[n][0] - positions[m][0]) / rmn,
                                        (positions[n][1] - positions[m][1]) / rmn};

        // 内積とノルムの積の計算
        double dot_product = velocities[n][0] * velocities[m][0] + velocities[n][1] * velocities[m][1];
        double norms_product = std::sqrt(velocities[n][0] * velocities[n][0] + velocities[n][1] * velocities[n][1]) *
                                std::sqrt(velocities[m][0] * velocities[m][0] + velocities[m][1] * velocities[m][1]);

        if (norms_product == 0) continue;

        double cos_theta = dot_product / norms_product;

        // 力の計算
        force_sum[0] += P(cos_theta) * V(rmn, c) * emn[0];
        force_sum[1] += P(cos_theta) * V(rmn, c) * emn[1];

        // 粒子nの速度を差し引く
        force_sum[0] -= velocities[n][0];
        force_sum[1] -= velocities[n][1];
    }

    // 加速度の更新
    new_accelerations[n][0] += a * force_sum[0];
    new_accelerations[n][1] += a * force_sum[1];

    // 速度の更新
    velocities[n][0] += new_accelerations[n][0] * dt;
    velocities[n][1] += new_accelerations[n][1] * dt;

    // 位置の更新
    positions[n][0] += velocities[n][0] * dt;
    positions[n][1] += velocities[n][1] * dt;

    accelerations[n][0] = new_accelerations[n][0];
    accelerations[n][1] = new_accelerations[n][1];

    // x軸方向の境界条件
    if (positions[n][0] >= width) positions[n][0] -= width;
    if (positions[n][0] < 0) positions[n][0] += width;

    // y軸方向の境界条件
    if (positions[n][1] >= height) positions[n][1] -= height;
    if (positions[n][1] < 0) positions[n][1] += height;


    // 境界を超えた場合のエラーチェック
    if (positions[n][0] > width || positions[n][1] > height || positions[n][0] < 0 || positions[n][1] < 0)
    {
        std::cerr << "Error: Particle " << n << " exceeded boundaries." << std::endl;
        throw std::out_of_range("Particle exceeded width or height boundary");
    }
    }
}

void run_simulation(Values &positions,
                    Values &velocities,
                    Values &accelerations,
                    int steps,
                    int num,
                    double r,
                    double dt,
                    double a,
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
        update(positions, velocities, accelerations, dt, a, c, num, width, height);

        if (i % 20 == 0) {
            if (ofs_csv_file.is_open()) {
                for (int j = 0; j < num; ++j) {
                    ofs_csv_file << positions[j][0] << "," << positions[j][1] << std::endl;
                }
            }
        }
    }
}