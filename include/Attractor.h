#ifndef ATTRACTOR_H
#define ATTRACTOR_H

#include <vector>
#include <array>

/**
 * @brief Base class for dynamic attractors
 * 
 * This abstract class defines the interface for all attractor implementations.
 * Subclasses must implement the step() method to define the differential equations.
 */
class Attractor {
public:
    /**
     * @brief Structure to hold a 3D point
     */
    struct Point3D {
        double x, y, z;
        
        Point3D(double x = 0.0, double y = 0.0, double z = 0.0)
            : x(x), y(y), z(z) {}
    };

    /**
     * @brief Constructor
     * @param initial_x Initial x coordinate
     * @param initial_y Initial y coordinate
     * @param initial_z Initial z coordinate
     */
    Attractor(double initial_x = 0.0, double initial_y = 0.0, double initial_z = 0.0);
    
    /**
     * @brief Virtual destructor
     */
    virtual ~Attractor() = default;

    /**
     * @brief Perform one integration step
     * @param dt Time step size
     * @return New point after integration
     */
    virtual Point3D step(double dt) = 0;

    /**
     * @brief Get current position
     */
    Point3D getPosition() const { return current_pos; }

    /**
     * @brief Set current position
     */
    void setPosition(const Point3D& pos) { current_pos = pos; }

    /**
     * @brief Reset to initial position
     */
    void reset();

    /**
     * @brief Get the trajectory history
     */
    const std::vector<Point3D>& getTrajectory() const { return trajectory; }

    /**
     * @brief Clear trajectory history
     */
    void clearTrajectory() { trajectory.clear(); }

    /**
     * @brief Set maximum trajectory length
     */
    void setMaxTrajectoryLength(size_t max_length) { max_trajectory_length = max_length; }

protected:
    Point3D current_pos;
    Point3D initial_pos;
    std::vector<Point3D> trajectory;
    size_t max_trajectory_length = 10000;
};

#endif // ATTRACTOR_H

