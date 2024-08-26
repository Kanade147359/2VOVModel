#include "simulation.hpp"
#include <iostream>
#include <vector>
#include <cmath>
#include <array>
#include <string>
#include <fstream>
#include <random>

const int X = 0;
const int Y = 1;

// 力関数
double V(double r, double alpha, double beta, double b, double c) {
    return alpha * (std::tanh(beta * (r - b)) + c);
}

double norm_product(std::array<double, 2> x){
    return std::sqrt(std::pow(x[0], 2) + std::pow(x[1], 2));
}

// 位置と速度の更新関数
void update(Values& positions, 
            Values& velocities, 
            Values& accelerations, 
            double dt, 
            NeighborIds neighbors, 
            double a,
            double alpha,
            double beta,
            double b, 
            double c,
            double eta,
            int num,
            double width,
            double height) {
    Values new_accelerations(num, {0.0, 0.0});

    for (int n = 0; n < num; ++n) {
        std::array<double, 2> force_sum = {0.0, 0.0};

        for (int k : neighbors[n]) {
            double rkj = std::sqrt(std::pow(positions[k][0] - positions[j][0], 2) + 
                                   std::pow(positions[k][1] - positions[j][1], 2));
            if (rkj == 0) continue;
            double nkj_x = (positions[k][0] - positions[j][0]) / rkj;
            double nkj_y = (positions[k][1] - positions[j][1]) / rkj;

            double cos_phi = (norm_product(positions[k]) - norm_product(positions[j])) / rkj;

            force_sum[0] += 
            force_sum[1] += 
        }
    
        new_accelerations[n][0] = a * force_sum[0];
        new_accelerations[n][1] = a * force_sum[1];

        velocities[n][0] += new_accelerations[n][0] * dt;
        velocities[n][1] += new_accelerations[n][1] * dt;

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(-M_PI, M_PI);

        double noise_angle = eta * dis(gen);

        // 現在の速度ベクトルの成分
        double vx = velocities[n][0];
        double vy = velocities[n][1];

        // 回転行列を使用してベクトルを回転させる
        double new_vx = vx * std::cos(noise_angle) - vy * std::sin(noise_angle);
        double new_vy = vx * std::sin(noise_angle) + vy * std::cos(noise_angle);

        // ノイズを加えた新しいベクトルを代入
        velocities[n][0] = new_vx;
        velocities[n][1] = new_vy;

        positions[n][0] += velocities[n][0] * dt;
        positions[n][1] += velocities[n][1] * dt;

        accelerations[n][0] = new_accelerations[n][0];
        accelerations[n][1] = new_accelerations[n][1];

        if (positions[n][0] >= width) {
            positions[n][0] -= width;
        }
        else if (positions[n][0] < 0) {
            positions[n][0] += width;         
        }

        if (positions[n][1] >= height) {
            positions[n][1] = height - (positions[n][1]-height);
            velocities[n][1] *= -1;         
        }
        else if (positions[n][1] < 0) {
            positions[n][1] = -positions[n][1];
            velocities[n][1] = -velocities[n][1];         
        }

        if (positions[n][0] > width) {
            std::cerr << "Error: Particle " << n << " exceeded width: "
                      << positions[n][0] << " > " << width << std::endl;
            throw std::out_of_range("Particle exceeded width boundary");
        } else if (positions[n][1] > height) {
            std::cerr << "Error: Particle " << n << " exceeded height: "
                      << positions[n][1] << " > " << height << std::endl;
            throw std::out_of_range("Particle exceeded height boundary");
        }
    }
}

NeighborIds find_neighbors(int num, const Values& positions, double distance_threshold) {

    NeighborIds neighbors(num);  

    for (int n = 0; n < num; ++n) {
        for (int m = 0; m < num; ++m) {
            if (n != m) {
                double distance = std::sqrt(std::pow(positions[n][0] - positions[m][0], 2) + 
                                            std::pow(positions[n][1] - positions[m][1], 2));
                if (distance <= distance_threshold) {
                    neighbors[n].push_back(m);  
                }
            }
        }
    }
    return neighbors;
}

void run_simulation(Values &positions,
                    Values &velocities,
                    Values &accelerations,
                    double distance_threshold,
                    int steps,
                    int num,
                    double r,
                    double dt,
                    double a,
                    double c,
                    double eta,
                    double width,
                    double height,
                    std::string filepath){
    auto neighbors = find_neighbors(num, positions, distance_threshold);

    std::ofstream ofs_csv_file(filepath);

    if (!ofs_csv_file.is_open()) {
        std::cerr << "Error opening file: " << filepath << std::endl;
        return;
    }

    for (int i = 0; i < steps; ++i){
        update(positions, velocities, accelerations, dt, neighbors, a, c,eta, num, width, height);

        if (i % 20 == 0) {
            if (ofs_csv_file.is_open()) {
                for (int j = 0; j < num; ++j) {
                    ofs_csv_file << positions[j][0] << "," << positions[j][1] << std::endl;
                }
            }
        }
    }
}