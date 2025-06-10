#include <iostream>
#include <vector>
#include <cstdlib>
#include <fstream>
#include "Vec2.hpp"
#include "Particle.hpp"
#include "Model.hpp"

int main() {
    const int nCols = 10;
    const int nRows = 5;
    const double spacing = 1.0;
    const double dy = spacing * std::sqrt(3.0) / 2.0;
    const int N = nCols * nRows;
    const int steps = 10000;
    std::vector<Particle> P(N);

    for (int i = 0; i < N; ++i) {
        int row = i / nCols;
        int col = i % nCols;
        double offset = (row % 2 == 0) ? 0.0 : spacing / 2.0;
        P[i].pos = {col * spacing + offset, row * dy};
        P[i].vel = {1, 0};
        P[i].acc = {0, 0};
    }

    std::ofstream ofs("positions.csv");
    ofs << "step";
    for(int i = 0; i < N; ++i) ofs << ",x" << i << ",y" << i;
    ofs << "\n";

    for (int step = 0; step < steps; ++step) {
        for (int i = 0; i < N; ++i) {
            P[i].acc = Model::computeAcceleration(P[i], P);
        }
        for (int i = 0; i < N; ++i) {
            P[i].vel += P[i].acc * Model::dt;
            P[i].pos += P[i].vel * Model::dt;
        }
        ofs << step;
        for(int i = 0; i < N; ++i) {
            ofs << "," << P[i].pos.x << "," << P[i].pos.y;
        }
        ofs << "\n";
    }
    ofs.close();
    std::cout << "Simulation completed. Results saved to positions.csv" << std::endl;
    return 0;
}



