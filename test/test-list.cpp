#include <iostream>

void add_by_2dlist(double A[][2], double B[][2], const int NUM){
    for (int i = 0; i < NUM; ++i){
        for (int j = 0; j < 2; ++j){
            A[i][j] += B[i][j];
        }
    }
}

int main(){

  const int NUM = 10;
  double A[NUM][2] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 10}, {11, 12}, {13, 14}, {15, 16}, {17, 18}, {19, 20}};
  double B[NUM][2] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 10}, {11, 12}, {13, 14}, {15, 16}, {17, 18}, {19, 20}};

  add_by_2dlist(A, B, NUM);
  for (int i = 0; i < NUM; ++i){
    for (int j = 0; j < 2; ++j){
      std::cout << A[i][j] << " ";
    }
    std::cout << std::endl;
  }
}