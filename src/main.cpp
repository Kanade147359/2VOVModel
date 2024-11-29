#include "initial_values.hpp" 
#include "simulation.hpp"
#include <iostream>

int main(){
    const int ROW_SIZE = 10;
    const size_t NUM = std::pow(ROW_SIZE, 2);
    const double r = 1.3;
    const double a = 0.5;
    const double b = 1.0;
    const double c = -1.0;
    const double dt = 0.01;
    const int STEPS = 10000;

    const double width = (std::sqrt(3)/2) * r * ROW_SIZE;
    const double height = ROW_SIZE * r;

    std::cout << "Width: " << width << ", Height: " << height << std::endl;

    std::string filepath = "output/positions.csv";

    double positions[NUM][2]; double velocities[NUM][2];
    generate_initial_positions(positions, ROW_SIZE, NUM, r); generate_initial_velocities(velocities, NUM);
    run_simulation(positions, velocities, steps, num, dt, a, b, c, width, height, filepath);
    return 0;
}
