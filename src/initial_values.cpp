#include <cmath>
#include <random>
#include "initial_values.hpp"

Values generate_initial_positions(int N, int num, double r) {
    Values positions(num, {0.0, 0.0});
    // 疑似乱数生成のためにstd::mt19937を使用
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count(); // 現在時刻からシードを生成
    std::mt19937 generator(seed);  // Mersenne Twisterエンジンを使用
    std::uniform_real_distribution<double> distribution(-0.005, 0.005);  // -0.005 ~ 0.005の範囲のノイズ
    int k=0;
    for (int i = 0; i <= N; ++i)
    {
        for (int j = 0; j < N; ++j) {

            double noise_x = distribution(generator);  // x方向のノイズ

            if (i % 2 == 0) {
                positions[k] = {(std::sqrt(3)*r/2) * i + r/2 , r * j + r/2 + noise_x};
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
    Values velocities(num,{4.0,0.0});
    return velocities;
}

Values generate_initial_accelerations(int num) {
    Values accelerations(num, {0.0,0.0});
    return accelerations;
}

