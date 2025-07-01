#include <cmath>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <fstream>

#include "People.hpp"
#include "SimulationInfo.hpp"
#include "Simulation.hpp"

void step_simulation(std::vector<People> &agents, SimulationInfo &si){
  for (auto &p : agents) {
    p.fx = 0.0;
    p.fy = 0.0;
  }

  // 近傍リストの更新
  update_neighbors(agents, si);

  // jが受ける力を各kから計算して積算
  for (int j = 0; j < agents.size(); ++j) {
    for (int k : agents[j].neighbors) {
      calculate_force(j, k, agents, si);
    }
  }

  // 運動量、位置の更新
  for (auto &p : agents) {
    p.vx += si.a * (p.v0_x + p.fx - p.vx) * si.dt;
    p.vy += si.a * (p.v0_y + p.fy - p.vy) * si.dt;

    p.x += p.vx * si.dt;
    p.y += p.vy * si.dt;

    // 周期境界条件
    if (p.x < 0) p.x += si.LX;
    if (p.x >= si.LX) p.x -= si.LX;
    if (p.y < 0) p.y += si.LY;
    if (p.y >= si.LY) p.y -= si.LY;
  }
}

void write_agent_frame(const std::vector<People> &agents) {
  // GIFアニメーション用の元データ(frame????.dat)の出力
  static int index = 0;
  std::ostringstream filename;
  filename << "frame" << std::setfill('0') << std::setw(4) << index << ".dat";

  std::ofstream ofs(filename.str());
  std::cout << "# " << filename.str() << std::endl;
  if (!ofs) {
    std::cerr << "Error: Failed to open file " << filename.str() << " for writing." << std::endl;
    return;
  }

  for (const auto &p : agents) {
    ofs << p.x << " " << p.y << " " << p.vx << " " << p.vy << "\n";
  }

  ++index;
}

// Pythonにあとで渡すためのYAMLファイルを作成
void save_yaml(SimulationInfo &si, const std::string &filename = "conf.yaml") {
  std::ofstream ofs(filename);
  if (!ofs) {
    std::cerr << "Error: Failed to open " << filename << " for writing." << std::endl;
    return;
  }

  ofs << std::fixed << std::setprecision(6);
  ofs << "LX: " << si.LX << "\n";
  ofs << "LY: " << si.LY << "\n";
}