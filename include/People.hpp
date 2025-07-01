#pragma once

#include <cmath>
#include <vector>
#include <random>
#include "SimulationInfo.hpp"

struct People {
    double x, y;
    double vx, vy;
    double fx, fy;
    double v0_x, v0_y;
    std::vector<int> neighbors;
};

void calculate_force(int j, int k, std::vector<People> &agents, SimulationInfo &si);
void update_neighbors(std::vector<People> &agents, SimulationInfo &si);
void initialize_agents_triangular_lattice(std::vector<People> &agents, SimulationInfo &si, const double r, std::mt19937 &rng);

