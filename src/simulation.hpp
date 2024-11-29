#ifndef Simulation_hpp
#define Simulation_hpp

#include <vector>
#include <array>
#include <string>

const int X = 0;
const int Y = 1;

void calculate_acceleration(double velocity[2], double neighbors[][2], double b, double c, double a, double &ax, double &ay);
void find_closest_neighbors(double positions[][2],double neighbors[][2],  int N, int NUM, double width, double height);
void sort_and_select_top_6(double neighbors[][2], double distances[][2]);

void update(double positions[][2], 
            double velocities[][2], 
            double dt, 
            double a, 
            double b,
            double c,
            int num,
            double width,
            double height);

void run_simulation(double positions[][2], 
                    double velocities[][2], 
                    int STEPS, 
                    int NUM, 
                    double dt, 
                    double a, 
                    double b,
                    double c,
                    double WIDTH,
                    double HEIGHT,
                    std::string filepath);

#endif // SIMULATION_H
