#pragma once
#include "dots.h"

struct face {
    dot3D start;
    dot3D end;
};

void draw_face(dot3D d1, dot3D d2);
