#pragma once
#include <vector>
#include "dots.h"


struct cube {
    dot3D center;
    float side;
    std::vector<dot3D> dots;
};

void draw_cube(cube c, dot3D camera);
cube construct_cube(dot3D center, float side);
