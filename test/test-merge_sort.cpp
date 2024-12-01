#include <cmath>
#include <iostream>

const int X = 0;
const int Y = 1;

void merge_sort(double A[][3], double B[][2], int left, int right);
void merge(double A[][3], double B[][2], int left, int mid, int right);

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
        if (L_A[j][2] <= R_A[k][2]) {
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

int main() {
    // テストデータ
    double A[6][3] = {
        {1, 0, 5.0},
        {2, 0, 3.0},
        {3, 0, 8.0},
        {4, 0, 1.0},
        {5, 0, 7.0},
        {6, 0, 2.0}
    };

    double B[6][2] = {
        {10.1, 20.2},
        {30.3, 40.4},
        {50.5, 60.6},
        {70.7, 80.8},
        {90.9, 100.1},
        {110.2, 120.3}
    };

    // ソート前の配列の状態を出力
    std::cout << "Before sorting:" << std::endl;
    for (int i = 0; i < 6; i++) {
        std::cout << "A[" << i << "][2]: " << A[i][2]
                  << " | B[" << i << "][X]: " << B[i][X]
                  << ", B[" << i << "][Y]: " << B[i][Y] << std::endl;
    }

    // マージソートを実行
    merge_sort(A, B, 0, 6);

    // ソート後の配列の状態を出力
    std::cout << "\nAfter sorting:" << std::endl;
    for (int i = 0; i < 6; i++) {
        std::cout << "A[" << i << "][2]: " << A[i][2]
                  << " | B[" << i << "][X]: " << B[i][X]
                  << ", B[" << i << "][Y]: " << B[i][Y] << std::endl;
    }

    return 0;
}