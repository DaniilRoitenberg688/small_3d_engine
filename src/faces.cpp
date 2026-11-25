#include "faces.h"
#include "raylib.h"


void draw_face(dot3D d1, dot3D d2) {
    dot2D dot2d = convert_3D_to_2D(d1);
    auto cors = prepare_dot_for_drawing(dot2d);
    int x1 = std::get<0>(cors) ;
    int y1 = std::get<1>(cors) ;
    dot2d = convert_3D_to_2D(d2);
    cors = prepare_dot_for_drawing(dot2d);
    int x2 = std::get<0>(cors);
    int y2 = std::get<1>(cors);
    DrawLine(x1, y1, x2, y2, GREEN);
}
