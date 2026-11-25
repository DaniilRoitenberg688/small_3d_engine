#pragma once
#include <vector>
#include "dots.h"


struct cube {
    dot3D center;
    float side;
    std::vector<dot3D> dots;
};

cube construct_cube(dot3D center, float side);
void draw_cube(cube c, dot3D camera, rotation rot);
