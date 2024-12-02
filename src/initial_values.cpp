#include <cmath>

#include "initial_values.hpp"

void generate_initial_positions(double positions[][2],int row_size, int num, double r) {

    int k=0;
    int col_size = row_size;
    
    for (int i = 0; i < col_size; ++i)
    {
        for (int j = 0; j < row_size; ++j) {

            if (i % 2 == 0) {
                positions[k][X] = std::sqrt(3)*r/2 * i + r/2;
                positions[k][Y] = r * j + r/2 ;
                ++k;
            }
            else {
                positions[k][X] = std::sqrt(3)*r/2 * i + r/2;
                positions[k][Y] = r * j + r / 2 + r / 2;
                ++k;
            }
        }
    }
}

void generate_initial_velocities(double velocities[][2], int NUM) {
    for (int i = 0; i < NUM; ++i) {
        velocities[i][X] = 1.0;
        velocities[i][Y] = 0.0;
    }
}

