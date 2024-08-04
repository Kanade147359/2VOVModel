#ifndef INITIAL_POSITIONS_HPP
#define INITIAL_POSITIONS_HPP

#include <vector>
#include <array>
#include <string>

using Values = std::vector<std::array<double, 2>>;

Values generate_initial_positions(int N, int num, double r);
Values generate_initial_velocities(int num);
Values generate_initial_accelerations(int num);

#endif 