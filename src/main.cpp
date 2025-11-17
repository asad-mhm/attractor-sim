#include <iostream>
#include "LorenzAttractor.h"
#include "Renderer.h"
#include <cmath>

int main() {
    // Create renderer
    Renderer renderer(1200, 800);
    
    if (!renderer.initialize()) {
        std::cerr << "Failed to initialize renderer!" << std::endl;
        return 1;
    }

    // Create Lorenz attractor with classic parameters
    LorenzAttractor lorenz(10.0, 28.0, 8.0/3.0, 0.0, 1.0, 0.0);
    lorenz.setMaxTrajectoryLength(5000);

    // Create Lorenz attractor with modified parameters
    LorenzAttractor lorenz_modified(10.0, 28.0, 8.0/3.0, 0.0, 0.99, 0.0);
    lorenz_modified.setMaxTrajectoryLength(5000);

    // Time step for integration
    const double dt = 0.01;

    std::cout << "Attractor Simulator" << std::endl;
    std::cout << "Controls:" << std::endl;
    std::cout << "  - Left mouse drag: Rotate view" << std::endl;
    std::cout << "  - Mouse wheel: Zoom in/out" << std::endl;
    std::cout << "  - ESC: Exit" << std::endl;

    // Main loop
    while (renderer.isOpen()) {
        renderer.handleEvents();
        
        // Update attractor
        lorenz.step(dt);
        
        // Render
        renderer.clear();
        renderer.render(lorenz);
        renderer.display();
    }

    return 0;
}

