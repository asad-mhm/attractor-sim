#ifndef RENDERER_H
#define RENDERER_H

#include <SFML/Graphics.hpp>
#include "Attractor.h"
#include <vector>

/**
 * @brief Class responsible for rendering attractors
 * 
 * Handles 3D to 2D projection, camera controls, and drawing the trajectory
 */
class Renderer {
public:
    /**
     * @brief Constructor
     * @param width Window width
     * @param height Window height
     */
    Renderer(unsigned int width = 800, unsigned int height = 600);

    /**
     * @brief Initialize the renderer
     */
    bool initialize();

    /**
     * @brief Check if window is open
     */
    bool isOpen() const;

    /**
     * @brief Handle events
     */
    void handleEvents();

    /**
     * @brief Clear the window
     */
    void clear();

    /**
     * @brief Render an attractor
     * @param attractor The attractor to render
     */
    void render(const Attractor& attractor);

    /**
     * @brief Display the rendered frame
     */
    void display();

    /**
     * @brief Close the window
     */
    void close();

    /**
     * @brief Get the SFML window (for additional controls if needed)
     */
    sf::RenderWindow& getWindow() { return window; }

    /**
     * @brief Set camera rotation
     */
    void setRotation(double angle_x, double angle_y);

    /**
     * @brief Set zoom level
     */
    void setZoom(double zoom);

    /**
     * @brief Get zoom level
     */
    double getZoom() const { return zoom_level; }

private:
    /**
     * @brief Project 3D point to 2D screen coordinates
     */
    sf::Vector2f project3D(const Attractor::Point3D& point) const;

    /**
     * @brief Apply rotation to a 3D point
     */
    Attractor::Point3D rotate3D(const Attractor::Point3D& point) const;

    sf::RenderWindow window;
    unsigned int width;
    unsigned int height;
    
    // Camera parameters
    double angle_x;
    double angle_y;
    double zoom_level;
    
    // Color gradient for trajectory
    sf::Color start_color;
    sf::Color end_color;
};

#endif // RENDERER_H

