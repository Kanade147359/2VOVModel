#pragma once

#include <vector>
#include "Vec2.hpp"
#include "Particle.hpp"

namespace Model {
    extern double a;
    extern double V0;
    extern double alpha;
    extern double b;
    extern double c_param;
    extern double dt;
		double F(Vec2 p_vel, Vec2 desired_vel);

    double interactionForce(double d);
    Vec2 computeAcceleration(const Particle& p, const std::vector<Particle>& all);
}