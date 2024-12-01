#ifndef Simulation_HPP
#define Simulation_HPP

#include <vector>
#include <array>
#include <string>

#include "constants.hpp"

void calculate_acceleration(double velocity[2], double neighbors[][2], double distances[][3], double a, double b, double c, double &ax, double &ay);
void find_neighbors(double positions[][2],double neighbors[][2], double distances[][3],  int n, int NUM, double width, double height);
void merge_sort(double A[][3], double B[][2], int left, int right);
void merge(double A[][3], double B[][2], int left, int mid, int right);

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
