#ifndef LORENZ_ATTRACTOR_H
#define LORENZ_ATTRACTOR_H

#include "Attractor.h"

/**
 * @brief Implementation of the Lorenz attractor
 * 
 * The Lorenz attractor is defined by the system of differential equations:
 *   dx/dt = σ(y - x)
 *   dy/dt = x(ρ - z) - y
 *   dz/dt = xy - βz
 * 
 * Classic parameters: σ = 10, ρ = 28, β = 8/3
 */
class LorenzAttractor : public Attractor {
public:
    /**
     * @brief Constructor
     * @param sigma Parameter σ (Prandtl number)
     * @param rho Parameter ρ (Rayleigh number)
     * @param beta Parameter β
     * @param initial_x Initial x coordinate
     * @param initial_y Initial y coordinate
     * @param initial_z Initial z coordinate
     */
    LorenzAttractor(double sigma = 10.0, double rho = 28.0, double beta = 8.0/3.0,
                    double initial_x = 0.0, double initial_y = 1.0, double initial_z = 0.0);

    /**
     * @brief Perform one integration step using Runge-Kutta 4th order
     * @param dt Time step size
     * @return New point after integration
     */
    Point3D step(double dt) override;

    /**
     * @brief Set parameters
     */
    void setParameters(double sigma, double rho, double beta);

    /**
     * @brief Get parameters
     */
    void getParameters(double& sigma, double& rho, double& beta) const;

private:
    /**
     * @brief Compute derivatives at a given point
     */
    Point3D derivatives(const Point3D& p) const;

    double sigma;  // σ parameter
    double rho;    // ρ parameter
    double beta;   // β parameter
};

#endif // LORENZ_ATTRACTOR_H

