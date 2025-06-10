#include "Model.hpp"
#include <cmath>

namespace Model {
    double a       = 1.0;
    double V0      = 1.0;
    double alpha   = 1.0;
    double b       = 1.0;
    double c = 0.0;
    double dt      = 0.01;
		Vec2 desiredVel = {1.0, 0.0}; 

    double F(Vec2 p_vel, Vec2 desired_vel) {
        double  cos_theta = p_vel.dot(desired_vel) / (p_vel.norm() * desired_vel.norm());
        return (cos_theta + 1.0) / 2.0;
    }

    double interactionForce(double d) {
        return std::tanh(alpha * (d - b)) + c;
    }

    Vec2 computeAcceleration(const Particle& p, const std::vector<Particle>& all) {
        Vec2 sumF{0.0, 0.0};
        for(const auto& other: all) {
            if (&p == &other) continue; // 自分自身は無視
            Vec2 diff = other.pos - p.pos;
            double dist = diff.norm();
            if (dist < 1e-6) continue;
            sumF += diff.normalized() * F(p.vel, desiredVel) * interactionForce(dist);
        }

        return ( desiredVel - sumF - p.vel ) * a;
    }
}