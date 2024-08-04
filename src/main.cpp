#include "initial_values.hpp" 
#include "simulation.hpp"
#include <iostream>

int main(){
    int N = 10;
    int num = std::pow(N, 2);
    double r = 0.5;
    double a = 0.5;
    double c = 0.5;
    double dt = 0.01;
    double distance_threshold = 0.5;
    int steps = 10000;

    double width = (std::sqrt(3)/2) * r * N;
    double height = N * r;

    std::cout << "Width: " << width << ", Height: " << height << std::endl;

    std::string filepath = "output/positions.csv";

    Values positions = generate_initial_positions(N, num, r);
    Values velocities = generate_initial_velocities(num);
    Values acceleration = generate_initial_accelerations(num);

    run_simulation(positions, velocities, acceleration, 
                   distance_threshold, steps, num, 
                   r, dt, a, c, 
                   width, height, 
                   filepath);
    return 0;
}