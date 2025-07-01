#pragma once

struct SimulationInfo {
  double LX, LY;
  const double alpha = 0.25;
  const double beta = 2.5;
  const double a = 0.5; // 感応度
  const double b = 1.0;
  const double c = -1.0;
  const double dt = 0.5; // 時間刻み
  const double R = 2.0;  // 隣接歩行者を探す距離
};