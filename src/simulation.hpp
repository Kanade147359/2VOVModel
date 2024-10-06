#ifndef Simulation_hpp
#define Simulation_hpp

#include <vector>
#include <array>
#include <string>

using Values = std::vector<std::array<double, 2>>;

// 構造体またはペアを使用して、距離と粒子のインデックスを保持
struct Neighbor {
    double dx;
    double dy;
    double distance;
};

std::vector<Neighbor> find_neighbors(Values& positions, int n, int num, double width, double height);

void calculate_acceleration(std::array<double, 2> velocity, std::vector<Neighbor> neighbors, double b, double c, double a, double &ax, double &ay);

void update(Values& positions, 
            Values& velocities, 
            double dt, 
            double a, 
            double b,
            double c,
            int num,
            double width,
            double height);

void run_simulation(Values& positions, 
                    Values& velocities, 
                    int steps, 
                    int num, 
                    double dt, 
                    double a, 
                    double b,
                    double c,
                    double width,
                    double height,
                    std::string filepath);

#endif // SIMULATION_H
