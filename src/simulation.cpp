#include "simulation.hpp"
#include "constants.hpp"
#include <iostream>
#include <cmath>
#include <string>
#include <fstream>

// 力関数
double V(double r, double b, double c) {
    return 0.25 * (std::tanh(2.5*(r - b)) + c);
}

void find_neighbors(double positions[][2],double neighbors[][2],double distances[][3], int n, int NUM, double width, double height){;
    int k = 0; // neighbors, distancesのindex
    for (int m = 0; m < NUM; ++m)
    {
        if (m == n) continue;
        double dx = positions[m][X] - positions[n][X];
        double dy = positions[m][Y] - positions[n][Y];

        if (dx < -width/2) dx += width;
        if (dx > width/2) dx -= width;
        if (dy < -height/2) dy += height;
        if (dy > height/2) dy -= height;

        double rmn = std::sqrt(dx*dx + dy*dy);

        neighbors[k][X] = positions[m][X]; neighbors[k][Y] = positions[m][Y];
        distances[k][0] = dx; distances[k][1] = dy; distances[k][2] = rmn;
        ++k;
    }
    merge_sort(distances, neighbors, 0, NUM-1);
}

void merge_sort(double A[][3], double B[][2], int left, int right){
    if (left + 1 < right) {
        int mid;

        mid = (left + right) / 2;

        merge_sort(A,B,left,mid);
        merge_sort(A,B,mid,right);

        merge(A, B, left, mid, right);
    }
}

void merge(double A[][3], double B[][2],int left, int mid, int right){
    int i, j, k;
    int n1 = mid - left;
    int n2 = right - mid;

    double L_A[n1 + 1][3], R_A[n2 + 1][3];
    double L_B[n1+1][2], R_B[n2+1][2];

    for (i = 0; i < n1; i++) {
        L_A[i][2] = A[left + i][2];
        L_B[i][X] = B[left + i][X];
        L_B[i][Y] = B[left + i][Y];
    }
    for (i = 0; i < n2; i++) {
        R_A[i][2] = A[mid + i][2];
        R_B[i][X] = B[mid + i][X];
        R_B[i][Y] = B[mid + i][Y];
    }

    L_A[n1][2] = INFINITY;
    R_A[n2][2] = INFINITY;

    j = 0;
    k = 0;

    for (i = left; i < right; i++)
    {
        if (L_A[j] <= R_A[k]) {
            A[i][2] = L_A[j][2];
            B[i][X] = L_B[j][X];
            B[i][Y] = L_B[j][Y];
            j++;
        } else {
            A[i][2] = R_A[k][2];
            B[i][X] = R_B[k][X];
            B[i][Y] = R_B[k][Y];
            k++;
        }
    }
}

void calculate_acceleration(double position[2], double velocity[2], double neighbors[][2], double distances[][3], double a, double b, double c, double &ax, double &ay)
{
    double F_sum_x = 0;
    double F_sum_y = 0;
    for (int i = 0; i < 6; ++i){
        double dx = neighbors[i][X] - position[X];
        double dy = neighbors[i][Y] - position[Y];
        double distance = std::sqrt(distances[i][0]*distances[i][0] + distances[i][1]*distances[i][1]);
        double emn[2];
        emn[X] = dx / distance; emn[Y] = dy / distance;
        double cos_phi = (neighbors[i][X] - position[X]) / distance;
        F_sum_x += V(distance, b, c) * (1 + cos_phi) * emn[0];
        F_sum_y += V(distance, b, c) * (1 + cos_phi) * emn[1];
    }
    ax = a * ((1.0 + F_sum_x) - velocity[X]);
    ay = a * (F_sum_y - velocity[Y]);
}

// 位置と速度の更新関数
void update(double positions[][2], 
            double velocities[][2], 
            double dt, 
            double a, 
            double b,
            double c,
            int num,
            double width,
            double height
            ) {
    // 速度の更新
    for (int n = 0; n < num; ++n){
        // ソートする配列
        double neighbors[num-1][2];//{X, Y}
        double distances[num-1][3];//{dx, dy, distance}
        find_neighbors(positions, neighbors, distances, n, num, width, height);
        double ax = 0.0;
        double ay = 0.0;
        calculate_acceleration(positions[n], velocities[n],neighbors, distances, b, c, a, ax, ay);
        velocities[n][0] += ax * dt; 
        velocities[n][1] += ay * dt;
    }
    // 位置の更新
    for (int i = 0; i < num; ++i){
        // 位置の更新

        positions[i][X] += velocities[i][X] * dt;
        positions[i][Y] += velocities[i][Y] * dt;

        // x軸方向の境界条件
        if (positions[i][X] >= width) positions[i][X] -= width;
        if (positions[i][X] < 0) positions[i][X] += width;

        // y軸方向の境界条件
        if (positions[i][Y] >= height) positions[i][Y] -= height;
        if (positions[i][Y] < 0) positions[i][Y] += height;

        //境界を超えた場合のエラーチェック
         for (int i = 0; i < num; ++i)
         {
         if (positions[i][X] > width || positions[i][Y] > height || positions[i][X] < 0 || positions[i][Y] < 0)
         {
             std::cerr << "Error: Particle " << i << " exceeded boundaries." << std::endl;
             throw std::out_of_range("Particle exceeded width or height boundary");
         }
         }
    }
}
void run_simulation(double positions[][2],
                    double velocities[][2],
                    int steps,
                    int num,
                    double dt,
                    double a,
                    double b,
                    double c,
                    double width,
                    double height,
                    std::string filepath){

    std::ofstream ofs_csv_file(filepath);

    if (!ofs_csv_file.is_open()) {
        std::cerr << "Error opening file: " << filepath << std::endl;
        return;
    }

    for (int i = 0; i < steps; ++i){
        update(positions, velocities, dt, a, b, c, num, width, height);
        if (i % 20 == 0) {
            if (ofs_csv_file.is_open()) {
                for (int j = 0; j < num; ++j) {
                    ofs_csv_file << positions[j][0] << "," << positions[j][1] << std::endl;
                }
            }
        }
    }
}