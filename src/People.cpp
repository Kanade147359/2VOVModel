#include "People.hpp"

void calculate_force(int j, int k, std::vector<People> &agents, SimulationInfo &si) {
	auto &pj = agents[j];
	const auto &pk = agents[k];

	double dx = pk.x - pj.x;
	double dy = pk.y - pj.y;

	if (dx < -si.LX * 0.5) dx += si.LX;
	if (dx > -si.LX * 0.5) dx += si.LX;
	if (dy < -si.LX * 0.5) dx += si.LY;
	if (dy > si.LX * 0.5) dx += si.LY;

	double r = std::sqrt(dx * dx + dy * dy);
	double v0_norm = std::sqrt(pj.v0_x * pj.v0_x + pj.v0_y * pj.v0_y);

	double cos_phi = (dx * pj.v0_x + dy * pj.v0_y) / (r * v0_norm);

	double n_x = dx / r;
	double n_y = dy / r;

	double force_magnitude = si.alpha * (std::tanh(si.beta * (r - si.b)) + si.c);
	// 全体の力積ベクトル
	double fx = force_magnitude * (1.0 + cos_phi) * n_x;
	double fy = force_magnitude * (1.0 + cos_phi) * n_y;

	pj.fx += fx;
	pj.fy += fy;
}
void update_neighbors(std::vector<People> &agents, SimulationInfo &si) {
	const int N = agents.size();
	const double R2 = si.R * si.R;

	for (auto &p : agents) {
		p.neighbors.clear();
	}

	for (int j = 0; j < N; ++j) {
		for (int k = j + 1; k < N; ++k) {
			double dx = agents[k].x - agents[j].x;
			double dy = agents[k].y - agents[j].y;

			if (dx < -si.LX * 0.5) dx += si.LX;
			if (dx > si.LX * 0.5) dx -= si.LX;
			if (dy < -si.LY * 0.5) dy += si.LY;
			if (dy > si.LY * 0.5) dy -= si.LY;

			double dist2 = dx * dx + dy * dy;

			if (dist2 <= R2) {
				agents[j].neighbors.push_back(k);
				agents[k].neighbors.push_back(j);
			}
		}
	}
}

void initialize_agents_triangular_lattice(std::vector<People> &agents, SimulationInfo &si, const double r, std::mt19937 &rng) {

	const int nx = 20;
	const int ny = 20;

	const double dx = r;
	const double dy = std::sqrt(3.0) / 2.0 * r;

  si.LX = nx * dx;
  si.LY = ny * dy;

  const int N = nx * ny;
  agents.clear();
  agents.reserve(N);

  std::uniform_real_distribution<double> jitter(-0.01, 0.01); // rに対する割合で揺らぎ

  for (int iy = 0; iy < ny; ++iy) {
    for (int ix = 0; ix < nx; ++ix) {
      People p;
      double x = ix * dx;
      double y = iy * dy;

      if (iy % 2 == 1) {
        x += dx / 2.0; // 奇数行はオフセット
      }

      x += jitter(rng);
      y += jitter(rng);

      p.x = x;
      p.y = y;
      p.vx = 1.0;
      p.vy = 0.0;
      p.v0_x = 1.0;
      p.v0_y = 0.0;

      agents.push_back(p);
    }
  }
}

