#ifndef Simulation_hpp
#define Simulation_hpp

#include <vector>
#include <array>
#include <string>

using Values = std::vector<std::array<double, 2>>;
using NeighborIds = std::vector<std::vector<int>>; 

void update(Values& positions, 
            Values& velocities, 
            Values& accelerations, 
            double dt, 
            const NeighborIds& neighbors, 
            double a, 
            double c,
            double eta);

NeighborIds find_neighbors(int num,
                    const Values& positions, 
                    double distance_threshold);

void run_simulation(Values& positions, 
                    Values& velocities, 
                    Values& accelerations, 
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
                    std::string filepath);

#endif // SIMULATION_H
