#ifndef Simulation_hpp
#define Simulation_hpp

#include <vector>
#include <array>
#include <string>

using Values = std::vector<std::array<double, 2>>;

void update(Values& positions, 
            Values& velocities, 
            Values& accelerations, 
            double dt, 
            double a, 
            double c);

void run_simulation(Values& positions, 
                    Values& velocities, 
                    Values& accelerations, 
                    int steps, 
                    int num, 
                    double r, 
                    double dt, 
                    double a, 
                    double c,
                    double width,
                    double height,
                    std::string filepath);

#endif // SIMULATION_H
