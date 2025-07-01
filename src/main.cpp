#include <iostream>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <sstream>


#include "Simulation.hpp"
#include "People.hpp"
#include "SimulationInfo.hpp"

void simulation() {
  SimulationInfo si;
  const int seed = 12346;
  std::mt19937 rng(seed);
  std::vector<People> agents;

  std::stringstream ss_stgraph; // 時空図用

  const double r = 1.3;
  initialize_agents_triangular_lattice(agents, si, r, rng);
  std::cout << "# " << si.LX << " " << si.LY << agents.size() << std::endl;
  write_agent_frame(agents);
  for (int i = 0; i < 400; i++) {
    step_simulation(agents, si);
    write_agent_frame(agents);
    for (auto &a : agents) {
      ss_stgraph << i * si.dt << " " << a.x << std::endl;
    }
  }
  save_yaml(si, "conf.yaml");

  // 時空図の保存
  std::ofstream ofs("spatio_temporal.dat");
  if (!ofs) {
    std::cerr << "Error: Failed to open spatio_temporal.dat for writing." << std::endl;
  } else {
    ofs << ss_stgraph.str();
  }
}

int main() {
  simulation();
}



