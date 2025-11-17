#include "Renderer.h"
#include <cmath>
#include <algorithm>
#include <optional>
#include <cstdint>

Renderer::Renderer(unsigned int width, unsigned int height)
    : width(width), height(height),
      angle_x(0.0), angle_y(0.0), zoom_level(1.0),
      start_color(255, 0, 0), end_color(0, 0, 255) {
}

bool Renderer::initialize() {
    window.create(sf::VideoMode({width, height}), "Attractor Simulator");
    window.setFramerateLimit(60);
    return window.isOpen();
}

bool Renderer::isOpen() const {
    return window.isOpen();
}

void Renderer::handleEvents() {
    while (std::optional<sf::Event> event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        } else if (auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->code == sf::Keyboard::Key::Escape) {
                window.close();
            }
        } else if (auto* mouseWheelScrolled = event->getIf<sf::Event::MouseWheelScrolled>()) {
            zoom_level += mouseWheelScrolled->delta * 0.1;
            zoom_level = std::max(0.1, std::min(10.0, zoom_level));
        }
    }

    // Mouse drag rotation
    static bool mouse_pressed = false;
    static sf::Vector2i last_mouse_pos;
    
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
        if (mouse_pressed) {
            sf::Vector2i delta = mouse_pos - last_mouse_pos;
            angle_y += delta.x * 0.01;
            angle_x += delta.y * 0.01;
        }
        last_mouse_pos = mouse_pos;
        mouse_pressed = true;
    } else {
        mouse_pressed = false;
    }
}

void Renderer::clear() {
    window.clear(sf::Color(10, 10, 20));
}

Attractor::Point3D Renderer::rotate3D(const Attractor::Point3D& point) const {
    // Rotate around Y axis
    double cos_y = std::cos(angle_y);
    double sin_y = std::sin(angle_y);
    double x1 = point.x * cos_y - point.z * sin_y;
    double z1 = point.x * sin_y + point.z * cos_y;
    
    // Rotate around X axis
    double cos_x = std::cos(angle_x);
    double sin_x = std::sin(angle_x);
    double y1 = point.y * cos_x - z1 * sin_x;
    double z2 = point.y * sin_x + z1 * cos_x;
    
    return Attractor::Point3D(x1, y1, z2);
}

sf::Vector2f Renderer::project3D(const Attractor::Point3D& point) const {
    // Apply rotation
    Attractor::Point3D rotated = rotate3D(point);
    
    // Apply zoom
    double scale = 50.0 * zoom_level;
    
    // Project to 2D (isometric-like projection)
    float x = width / 2.0f + static_cast<float>(rotated.x * scale);
    float y = height / 2.0f - static_cast<float>(rotated.y * scale);
    
    return sf::Vector2f(x, y);
}

void Renderer::render(const Attractor& attractor) {
    const auto& trajectory = attractor.getTrajectory();
    
    if (trajectory.size() < 2) {
        return;
    }

    // Draw trajectory as connected lines with color gradient
    sf::VertexArray lines(sf::PrimitiveType::LineStrip, trajectory.size());
    
    for (size_t i = 0; i < trajectory.size(); ++i) {
        sf::Vector2f screen_pos = project3D(trajectory[i]);
        lines[i].position = screen_pos;
        
        // Color gradient from start to end
        float t = static_cast<float>(i) / static_cast<float>(trajectory.size() - 1);
        lines[i].color = sf::Color(
            static_cast<std::uint8_t>(start_color.r * (1.0f - t) + end_color.r * t),
            static_cast<std::uint8_t>(start_color.g * (1.0f - t) + end_color.g * t),
            static_cast<std::uint8_t>(start_color.b * (1.0f - t) + end_color.b * t)
        );
    }
    
    window.draw(lines);
    
    // Draw current position as a circle
    Attractor::Point3D current = attractor.getPosition();
    sf::Vector2f current_screen = project3D(current);
    
    sf::CircleShape current_point(5.0f);
    current_point.setPosition({current_screen.x - 5.0f, current_screen.y - 5.0f});
    current_point.setFillColor(sf::Color::White);
    window.draw(current_point);
}

void Renderer::display() {
    window.display();
}

void Renderer::close() {
    window.close();
}

void Renderer::setRotation(double angle_x, double angle_y) {
    this->angle_x = angle_x;
    this->angle_y = angle_y;
}

void Renderer::setZoom(double zoom) {
    zoom_level = zoom;
}

