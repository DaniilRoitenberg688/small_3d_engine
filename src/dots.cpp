#include "dots.h"
#include <cmath>
#include "constants.h"
#include "raylib.h"


dot2D convert_3D_to_2D(dot3D d) {
    dot2D d2;
    d2.x = d.x / d.z;
    d2.y = d.y / d.z;
    return d2;
}

std::tuple<int, int> prepare_dot_for_drawing(dot2D dot) {
    int x = (SCREEN_WIDTH / 2) + dot.x * (SCREEN_WIDTH / 2);
    int y = (SCREEN_HEIGHT / 2) + (0 - dot.y) * (SCREEN_HEIGHT / 2);
    return {x, y};
}


void rotate_dot (dot3D& d, float angle, dot3D center) {
    float old_x = d.x - center.x;
    float old_y = d.y - center.y;
    float old_z = d.z - center.z;

    d.x = old_x * cos(angle) + old_z * sin(angle) + center.z;
    d.y = old_y + center.y;
    d.z = -old_x * sin(angle) + old_z * cos(angle) + center.z;
}


void draw_dot(dot3D d) {
    dot2D dot2d = convert_3D_to_2D(d);
    auto cors = prepare_dot_for_drawing(dot2d);
    int x = std::get<0>(cors) ;
    int y = std::get<1>(cors) ;
    DrawRectangle(x - SIDE_SIZE / 2, y - SIDE_SIZE / 2, SIDE_SIZE, SIDE_SIZE, GREEN);
}

// void rotate_dots(float angle) {
//     for (auto i = DOTS.begin(); i != DOTS.end(); i++) {
//         rotate_dot(*i, angle);
//     }
// }
