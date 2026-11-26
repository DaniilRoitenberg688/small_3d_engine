#include "dots.h"
#include <cmath>
#include "constants.h"
#include "raylib.h"
#include "rotation.h"


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


dot3D rotate_point(dot3D center, dot3D point, rotation rot) {
    float x = point.x - center.x;
    float y = point.y - center.y;
    float z = point.z - center.z;

    // Y
    float x1 = x * cosf(rot.angle_y) + z * sinf(rot.angle_y);
    float z1 = -x * sinf(rot.angle_y) + z * cosf(rot.angle_y);

    x = x1;
    z = z1;

    // X
    float y1 = y * cosf(rot.angle_x) - z * sinf(rot.angle_x);
    float z2 = y * sinf(rot.angle_x) + z * cosf(rot.angle_x);

    y = y1;
    z = z2;

    return {
        x + center.x,
        y + center.y,
        z + center.z
    };
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
