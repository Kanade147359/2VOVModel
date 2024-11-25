#ifndef Simulation_hpp
#define Simulation_hpp

#include <vector>
#include <array>
#include <string>

const int X = 0;
const int Y = 1;

using Values = std::vector<std::array<double, 2>>;

void calculate_acceleration(std::array<double, 2> position, std::array<double, 2> velocity, Values neighbors, double a, double b, double c, double &ax, double &ay);
Values find_neighbors(Values& positions, int j, int num, double width, double height);
Values sort_and_select_top_6(const Values& positions, const std::vector<double>& distances);

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
