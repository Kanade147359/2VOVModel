#ifndef INITIAL_POSITIONS_HPP
#define INITIAL_POSITIONS_HPP

#include <vector>
#include <array>
#include <string>

const int X = 0;
const int Y = 1;

void generate_initial_positions(double* positions[][2], int N, int NUM, double r);
void generate_initial_velocities(double* velocities[][2],int NUM);

#endif 