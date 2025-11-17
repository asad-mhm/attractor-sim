#include "Attractor.h"

Attractor::Attractor(double initial_x, double initial_y, double initial_z)
    : current_pos(initial_x, initial_y, initial_z),
      initial_pos(initial_x, initial_y, initial_z) {
}

void Attractor::reset() {
    current_pos = initial_pos;
    trajectory.clear();
}

