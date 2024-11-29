#include <cmath>
#include <random>
#include "initial_values.hpp"

void generate_initial_positions(double* positions[][2], int ROW_SIZE, int NUM, double r) {

    int k=0;
    for (int i = 0; i <= NUM; ++i)
    {
        for (int j = 0; j < NUM; ++j) {

            if (i % 2 == 0) {
                positions[k][0] = std::sqrt(3)*r/2 * i + r/2;
                positions[k][1] = r * j + r/2 ;
                ++k;
            }
            else {
                positions[k][0] = std::sqrt(3)*r/2) * i + r/2;
                positions[k][1] = r * j + r / 2 + r / 2;
                ++k;
            }
        }
    }
}

void generate_initial_velocities(double* velocities[][2], int NUM) {
    for (int i = 0; i < NUM; ++i) {
        velocities[i][0] = 1.0;
    }
}

