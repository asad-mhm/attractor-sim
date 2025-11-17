#include "LorenzAttractor.h"
#include <cmath>

LorenzAttractor::LorenzAttractor(double sigma, double rho, double beta,
                                 double initial_x, double initial_y, double initial_z)
    : Attractor(initial_x, initial_y, initial_z),
      sigma(sigma), rho(rho), beta(beta) {
}

Attractor::Point3D LorenzAttractor::derivatives(const Point3D& p) const {
    Point3D d;
    d.x = sigma * (p.y - p.x);
    d.y = p.x * (rho - p.z) - p.y;
    d.z = p.x * p.y - beta * p.z;
    return d;
}

Attractor::Point3D LorenzAttractor::step(double dt) {
    // Runge-Kutta 4th order method
    Point3D k1 = derivatives(current_pos);
    Point3D k2 = derivatives(Point3D(
        current_pos.x + dt * k1.x / 2.0,
        current_pos.y + dt * k1.y / 2.0,
        current_pos.z + dt * k1.z / 2.0
    ));
    Point3D k3 = derivatives(Point3D(
        current_pos.x + dt * k2.x / 2.0,
        current_pos.y + dt * k2.y / 2.0,
        current_pos.z + dt * k2.z / 2.0
    ));
    Point3D k4 = derivatives(Point3D(
        current_pos.x + dt * k3.x,
        current_pos.y + dt * k3.y,
        current_pos.z + dt * k3.z
    ));

    // Update position
    current_pos.x += dt * (k1.x + 2.0 * k2.x + 2.0 * k3.x + k4.x) / 6.0;
    current_pos.y += dt * (k1.y + 2.0 * k2.y + 2.0 * k3.y + k4.y) / 6.0;
    current_pos.z += dt * (k1.z + 2.0 * k2.z + 2.0 * k3.z + k4.z) / 6.0;

    // Add to trajectory
    trajectory.push_back(current_pos);
    
    // Limit trajectory length
    if (trajectory.size() > max_trajectory_length) {
        trajectory.erase(trajectory.begin());
    }

    return current_pos;
}

void LorenzAttractor::setParameters(double sigma, double rho, double beta) {
    this->sigma = sigma;
    this->rho = rho;
    this->beta = beta;
}

void LorenzAttractor::getParameters(double& sigma, double& rho, double& beta) const {
    sigma = this->sigma;
    rho = this->rho;
    beta = this->beta;
}

