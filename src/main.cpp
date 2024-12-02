#include "initial_values.hpp" 
#include "simulation.hpp"
#include "constants.hpp"
#include <iostream>

int main(){
    int row_size = 10;
    size_t num = std::pow(row_size, 2);
    double r = 1.3;
    double a = 0.5;
    double b = 1.0;
    double c = -1.0;
    double dt = 0.01;
    int STEPS = 10000;

    const double width = (std::sqrt(3)/2) * r * row_size;
    const double height = row_size * r;

    std::string filepath = "output/positions.csv";

    double positions[num][2]; double velocities[num][2];
    generate_initial_positions(positions,row_size, num, r); generate_initial_velocities(velocities, num);
    run_simulation(positions, velocities, STEPS, num, dt, a, b, c, width, height, filepath);
    return 0;
}
