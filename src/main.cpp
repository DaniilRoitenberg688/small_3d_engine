#include <cmath>
#include <vector>
#include "objects.h"
#include "raylib.h"




const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;
const int SIDE_SIZE = 10;




cube construct_cube(dot3D center, float side) {
    std::vector<dot3D> dots = {
  {center.x + side / 2, center.y + side / 2, center.z + side / 2},
  {center.x + side / 2, center.y + side / 2, center.z - side / 2},
  {center.x + side / 2, center.y - side / 2, center.z + side / 2},
  {center.x + side / 2, center.y - side / 2, center.z - side / 2},
  {center.x - side / 2, center.y + side / 2, center.z + side / 2},
  {center.x - side / 2, center.y + side / 2, center.z - side / 2},
  {center.x - side / 2, center.y - side / 2, center.z + side / 2},
  {center.x - side / 2, center.y - side / 2, center.z - side / 2},
};
    std::vector<face> faces(12);
    for (dot3D d1 : dots) {
      for (dot3D d2 : dots) {
          int ex = d1.x == d2.x;
          int ey = d1.y == d2.y;
          int ez = d1.z == d2.z;
          if (ex + ey + ez == 2) {
              faces.push_back({d1, d2});
          }
      }

    }
    return cube {center, side, dots, faces};
}

std::vector<cube> init_cubes(std::vector<dot3D> centers) {

    std::vector<cube> cubes(centers.size());
    for (dot3D c : centers) {
        cubes.push_back(construct_cube(c, 1));
    }
    return cubes;
}



// const angle
dot2D convert_3D_to_2D(dot3D d) {
    dot2D d2;
    d2.x = d.x / d.z;
    d2.y = d.y / d.z;
    return d2;
}

std::tuple<int, int> prepare_dot_for_drawing(dot2D dot) {
    int x = (SCREEN_WIDTH / 2) + dot.x * (SCREEN_WIDTH / 2) + SIDE_SIZE / 2;
    int y = (SCREEN_HEIGHT / 2) + (0 - dot.y) * (SCREEN_HEIGHT / 2) + SIDE_SIZE / 2;
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
    DrawRectangle(x, y, SIDE_SIZE, SIDE_SIZE, GREEN);
}

void draw_cube(cube c) {
    for (auto i = c.dots.begin(); i != c.dots.end(); i++) {
        draw_dot(*i);
    }
}

void draw_line(dot3D d1, dot3D d2) {
    dot2D dot2d = convert_3D_to_2D(d1);
    auto cors = prepare_dot_for_drawing(dot2d);
    int x1 = std::get<0>(cors) + SIDE_SIZE / 2;
    int y1 = std::get<1>(cors) + SIDE_SIZE / 2;
    dot2d = convert_3D_to_2D(d2);
    cors = prepare_dot_for_drawing(dot2d);
    int x2 = std::get<0>(cors) + SIDE_SIZE / 2;
    int y2 = std::get<1>(cors) + SIDE_SIZE / 2;
    DrawLine(x1, y1, x2, y2, GREEN);
}

void draw_cube_faces(cube c) {
    for (auto i = c.faces.begin(); i != c.faces.end(); i++) {
        draw_line((*i).start, (*i).end);
    }
}


// void rotate_dots(float angle) {
//     for (auto i = DOTS.begin(); i != DOTS.end(); i++) {
//         rotate_dot(*i, angle);
//     }
// }

void draw_cubes(std::vector<cube> cubes) {
  for (cube c : cubes) {
      draw_cube(c);
      draw_cube_faces(c);
  }

}


int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Test");
    SetTargetFPS(60);


    std::vector<dot3D> centers = {
        {0, 0, 2},
        {1, 0, 2},
        {-1, 0, 2},
        {-1, 1, 2},
        {1, 1, 2},
        {0, 1, 2 }};
    std::vector<cube> cubes = init_cubes(centers);


    while (!WindowShouldClose()) {
        BeginDrawing();
        float angle = 90 * DEG2RAD * GetFrameTime();
        ClearBackground(BLACK);
        draw_cubes(cubes);
        // rotate_dots(angle);
        EndDrawing();

    }
    CloseWindow();
    return 0;
}
