#include <vector>
#include "dots.h"
#include "cube.h"
#include "faces.h"
#include "constants.h"
#include "raylib.h"


dot3D camera = {0, 0, 0};


std::vector<cube> init_cubes(std::vector<dot3D> centers) {

    std::vector<cube> cubes(centers.size());
    for (dot3D c : centers) {
        cubes.push_back(construct_cube(c, 1));
    }
    return cubes;
}


void draw_cubes(std::vector<cube> cubes) {
  for (cube c : cubes) {
      draw_cube(c, camera);
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
        if (IsKeyDown(KEY_DOWN)) {
            camera.z -= 1 * GetFrameTime();
        }
        if (IsKeyDown(KEY_UP)) {
            camera.z += 1 * GetFrameTime();
        }
        if (IsKeyDown(KEY_LEFT)) {
            camera.x -= 1 * GetFrameTime();
        }
        if (IsKeyDown(KEY_RIGHT)) {
            camera.x += 1 * GetFrameTime();
        }
        float angle = 90 * DEG2RAD * GetFrameTime();
        ClearBackground(BLACK);
        draw_cubes(cubes);
        // rotate_dots(angle);
        EndDrawing();

    }
    CloseWindow();
    return 0;
}
