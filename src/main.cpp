#include "initial_values.hpp" 
#include "simulation.hpp"
#include <iostream>

int main(){
    int N = 2;
    int num = 2; // std::pow(N, 2);
    double r = 1.3;
    double a = 0.5;
    double b = 1.0;
    double c = -1.0;
    double dt = 0.01;    
    int steps = 1000;

    double width = 5; //(std::sqrt(3)/2) * r * N;
    double height = 5; // N * r;

    std::cout << "Width: " << width << ", Height: " << height << std::endl;

    std::string filepath = "output/positions.csv";

    Values positions = generate_initial_positions(N, num, r);
    Values velocities = generate_initial_velocities(num);

    std::cout << "Start simulation" << std::endl;

    run_simulation(positions, velocities, steps, num, dt, a, b, c, width, height, filepath);

    std::cout << "Simulation finished" << std::endl;
    return 0;
}
