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
bool check_if_dot_can_be_seen(dot3D d, dot3D cd, rotation c_r);
dot3D intersect_surface_and_line(dot3D d1, dot3D d2, rotation r, dot3D cd);
