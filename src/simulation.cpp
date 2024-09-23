#include "simulation.hpp"
#include <iostream>
#include <vector>
#include <cmath>
#include <array>
#include <string>
#include <fstream>

// 角度依存性関数
double P(double cos_theta) {
    return 0.5 * (1 + cos_theta);
}

// 力関数
double V(double r, double c) {
    return std::tanh(r - c) + std::tanh(c);
}

// 位置と速度の更新関数
void update(Values& positions, 
            Values& velocities, 
            Values& accelerations, 
            double dt, 
            NeighborIds neighbors, 
            double a, 
            double c,
            int num,
            double width,
            double height) {
    Values new_accelerations(num, {0.0, 0.0});

    for (int n = 0; n < num; ++n) {
        std::array<double, 2> force_sum = {0.0, 0.0};

        for (int m : neighbors[n]) {
            double rmn = std::abs(std::sqrt(std::pow(positions[n][0] - positions[m][0], 2) + 
                                   std::pow(positions[n][1] - positions[m][1], 2)));
            if (rmn == 0) continue;
            std::array<double, 2> emn = {(positions[n][0] - positions[m][0]) / rmn, 
                          (positions[n][1] - positions[m][1]) / rmn};

            double dot_product = velocities[n][0] * velocities[m][0] + velocities[n][1] * velocities[m][1];
            double norms_product = std::abs(std::sqrt(velocities[n][0] * velocities[n][0] + velocities[n][1] * velocities[n][1])) * 
                                   std::abs(std::sqrt(velocities[m][0] * velocities[m][0] + velocities[m][1] * velocities[m][1]));
            if (norms_product == 0) continue;

            double cos_theta = dot_product / norms_product;

            force_sum[0] += P(cos_theta) * V(rmn, c) * emn[0];
            force_sum[1] += P(cos_theta) * V(rmn, c) * emn[1];

            force_sum[0] -= velocities[n][0];
            force_sum[1] -= velocities[n][1];
        }

        new_accelerations[n][0] += a * force_sum[0];
        new_accelerations[n][1] += a * force_sum[1];

        velocities[n][0] += new_accelerations[n][0] * dt;
        velocities[n][1] += new_accelerations[n][1] * dt;

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
            positions[n][1] = height;
            velocities[n][1] = - std::abs(velocities[n][1]);         
        }
        else if (positions[n][1] < 0) {
            positions[n][1] = 0;
            velocities[n][1] = - std::abs(velocities[n][1]);         
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
        update(positions, velocities, accelerations, dt, neighbors, a, c, num, width, height);

        if (i % 20 == 0) {
            if (ofs_csv_file.is_open()) {
                for (int j = 0; j < num; ++j) {
                    ofs_csv_file << positions[j][0] << "," << positions[j][1] << std::endl;
                }
            }
        }
    }
}