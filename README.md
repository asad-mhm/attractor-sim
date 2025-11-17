# Attractor Simulator

A C++ application for visualizing and modeling dynamic attractors, starting with the classic Lorenz attractor.

## Features

- **Lorenz Attractor**: Implementation of the famous Lorenz system with classic parameters (σ=10, ρ=28, β=8/3)
- **Real-time Visualization**: Interactive 3D visualization using SFML
- **Extensible Architecture**: Base `Attractor` class allows easy addition of new attractor types
- **Runge-Kutta Integration**: 4th order RK method for accurate numerical integration
- **Interactive Controls**: Mouse-based rotation and zoom

## Requirements

- C++17 compatible compiler (GCC 7+, Clang 5+)
- Make
- SFML 2.5 or higher

### Installing SFML

**macOS (using Homebrew):**
```bash
brew install sfml
```

**Ubuntu/Debian:**
```bash
sudo apt-get install libsfml-dev
```

**Windows:**
Download from [SFML website](https://www.sfml-dev.org/download.php) or use vcpkg:
```bash
vcpkg install sfml
```

## Building

```bash
# Build the project
make

# Or build and run in one command
make run
```

The executable will be created in `build/bin/AttractorSim`.

### Additional Make Targets

- `make clean` - Remove build artifacts
- `make rebuild` - Clean and rebuild
- `make run` - Build and run the program
- `make help` - Show available targets

## Running

```bash
# After building
./build/bin/AttractorSim

# Or use make run
make run
```

## Controls

- **Left Mouse Drag**: Rotate the 3D view
- **Mouse Wheel**: Zoom in/out
- **ESC**: Exit the application

## Project Structure

```
attractor-sim/
├── Makefile                # Build configuration
├── include/                # Header files
│   ├── Attractor.h        # Base attractor class
│   ├── LorenzAttractor.h  # Lorenz attractor implementation
│   └── Renderer.h         # Visualization renderer
├── src/                    # Source files
│   ├── main.cpp           # Application entry point
│   ├── Attractor.cpp
│   ├── LorenzAttractor.cpp
│   └── Renderer.cpp
└── README.md
```

## Adding New Attractors

To add a new attractor type:

1. Create a new class inheriting from `Attractor`
2. Implement the `step(double dt)` method with your differential equations
3. Add the header to `include/` and implementation to `src/`
4. The Makefile will automatically pick up new `.cpp` files in `src/`

Example:
```cpp
class MyAttractor : public Attractor {
public:
    MyAttractor(...) : Attractor(...) {}
    Point3D step(double dt) override {
        // Implement your differential equations
    }
};
```

## License

See LICENSE file for details.
