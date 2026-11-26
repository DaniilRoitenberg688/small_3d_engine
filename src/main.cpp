#include <cmath>
#include <vector>
#include "dots.h"
#include "cube.h"
#include "constants.h"
#include "raylib.h"
#include "rotation.h"




dot3D camera = {0, 0, 0};
rotation camera_rotation = {0, 0, 0};



std::vector<cube> init_cubes(std::vector<dot3D> centers) {

    std::vector<cube> cubes;
    for (dot3D c : centers) {
        cubes.push_back(construct_cube(c, 1));
    }
    return cubes;
}


void draw_cubes(std::vector<cube> cubes) {
  for (cube c : cubes) {
      draw_cube(c, camera, camera_rotation);
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
        {0, 1, 3 }};
    std::vector<cube> cubes = init_cubes(centers);


    while (!WindowShouldClose()) {
        BeginDrawing();
        if (IsKeyDown(KEY_W)) {
            camera.z += 1 * GetFrameTime() * cos(camera_rotation.angle_x) * cos(camera_rotation.angle_y);;
            camera.y -= 1 * GetFrameTime() * sin(camera_rotation.angle_x)                                ;
            camera.x += 1 * GetFrameTime() * sin(camera_rotation.angle_y) * cos(camera_rotation.angle_x);;
        }
        if (IsKeyDown(KEY_S)) {
            camera.z -= 1 * GetFrameTime() * cos(camera_rotation.angle_x) * cos(camera_rotation.angle_y);
            camera.y += 1 * GetFrameTime() * sin(camera_rotation.angle_x);
            camera.x -= 1 * GetFrameTime() * sin(camera_rotation.angle_y) * cos(camera_rotation.angle_x);
        }
        if (IsKeyDown(KEY_A)) {
            camera.x -= 1 * GetFrameTime() * cos(camera_rotation.angle_y);
            camera.z += 1 * GetFrameTime() * sin(camera_rotation.angle_y);
        }
        if (IsKeyDown(KEY_D)) {
            camera.x += 1 * GetFrameTime() * cos(camera_rotation.angle_y);
            camera.z -= 1 * GetFrameTime() * sin(camera_rotation.angle_y);
        }
        if (IsKeyDown(KEY_UP)) {
            camera_rotation.angle_x -= 1 * GetFrameTime();
        }
        if (IsKeyDown(KEY_DOWN)) {
            camera_rotation.angle_x += 1 * GetFrameTime();
        }
        if (IsKeyDown(KEY_RIGHT)) {
            camera_rotation.angle_y += 1 * GetFrameTime();
        }
        if (IsKeyDown(KEY_LEFT)) {
            camera_rotation.angle_y -= 1 * GetFrameTime();
        }
        ClearBackground(BLACK);
        draw_cubes(cubes);
        // rotate_dots(angle);
        EndDrawing();

    }
    CloseWindow();
    return 0;
}
