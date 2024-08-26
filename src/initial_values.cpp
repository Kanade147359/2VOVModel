#include <cmath>
#include <random>
#include "initial_values.hpp"

Values generate_initial_positions(int N, int num, double r) {
    Values positions(num, {0.0, 0.0});
    // i:
    int k=0;
    for (int i = 0; i <= N; ++i)
    {
        for (int j = 0; j < N; ++j) {
            if (i % 2 == 0) {
                positions[k] = {(std::sqrt(3)*r/2) * i + r/2 , r * j + r/2};
                ++k;
            }
            else {
                positions[k] = {(std::sqrt(3)*r/2) * i + r/2, r * j + r/2 + r/2};
                ++k;
            }
        }
    }
    return positions;
}

Values generate_initial_velocities(int num) {
    Values velocities(num,{0.5,0.0});
    return velocities;
}

Values generate_initial_accelerations(int num) {
    Values accelerations(num, {0.0,0.0});
    return accelerations;
}

