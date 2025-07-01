#pragma once

#include <vector>
#include <string>
#include "People.hpp"
#include "SimulationInfo.hpp"

void step_simulation(std::vector<People> &agents, SimulationInfo &si);
void write_agent_frame(const std::vector<People> &agents);
void save_yaml(SimulationInfo &si, const std::string &filename);
