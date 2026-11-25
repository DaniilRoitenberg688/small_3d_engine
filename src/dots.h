#pragma once
#include <tuple>

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


void rotate_dot (dot3D& d, float angle, dot3D center);

void draw_dot(dot3D d);
