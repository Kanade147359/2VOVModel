#include <cmath>
#include <random>
#include "initial_values.hpp"

Values generate_initial_positions(int N, int num, double r) {
    // Values positions(num, {0.0, 0.0});
    // int k=0;
    // for (int i = 0; i <= N; ++i)
    // {
    //     for (int j = 0; j < N; ++j) {

    //         if (i % 2 == 0) {
    //             positions[k] = {(std::sqrt(3)*r/2) * i + r/2 , r * j + r/2 };
    //             ++k;
    //         }
    //         else {
    //             positions[k] = {(std::sqrt(3)*r/2) * i + r/2, r * j + r/2 + r/2};
    //             ++k;
    //         }
    //     }
    // }
    // for test purposes, we will generate two particles with the same y-value
    // Create two particles with the same y-value
    Values positions(2, {0.0, 0.0});
    positions[0] = {r, r};       // First particle at (r, r)
    positions[1] = {r + r, r};   // Second particle at (r + r, r)
    return positions;
}

Values generate_initial_velocities(int num) {
    // Values velocities(num,{1.0,0.0});
        Values velocities(2, {0.0, 0.0});
    velocities[0] = {1.0, 0.0};  // First particle moving in the x-direction
    velocities[1] = {0.0, 0.0};  // Second particle stationary
    return velocities;
}


