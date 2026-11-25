#pragma once
#include <tuple>
#include "rotation.h"

struct dot3D {
    float x;
    float y;
    float z;
};


struct dot2D {
    float x;
    float y;
};

std::tuple<int, int> prepare_dot_for_drawing(dot2D dot);

dot2D convert_3D_to_2D(dot3D d);


dot3D rotate_point(dot3D center, dot3D point, rotation rot);

void draw_dot(dot3D d);
