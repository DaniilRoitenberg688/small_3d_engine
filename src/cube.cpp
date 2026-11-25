#include "cube.h"
#include "dots.h"
#include "faces.h"
#include "rotation.h"

cube construct_cube(dot3D center, float side) {
    std::vector<dot3D> dots = {
  {+ side / 2, + side / 2, + side / 2},
  {+ side / 2, + side / 2, - side / 2},
  {+ side / 2, - side / 2, + side / 2},
  {+ side / 2, - side / 2, - side / 2},
  {- side / 2, + side / 2, + side / 2},
  {- side / 2, + side / 2, - side / 2},
  {- side / 2, - side / 2, + side / 2},
  {- side / 2, - side / 2, - side / 2},
};
    return cube {center, side, dots};
}

std::vector<face> generate_cube_faces(const std::vector<dot3D>& dots) {
    std::vector<face> faces;
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
    return faces;
}

std::vector<dot3D> prepare_cube_for_drawing(cube c, dot3D camera) {
    std::vector<dot3D> dots;
    for (dot3D d : c.dots) {
      dots.push_back({
          d.x + c.center.x - camera.x,
          d.y + c.center.y - camera.y,
          d.z + c.center.z - camera.z
      });
    }
    return dots;

}

void draw_cube(cube c, dot3D camera, rotation r) {
    std::vector<dot3D> dots_prepared = prepare_cube_for_drawing(c, camera);
    for (dot3D d : dots_prepared) {
        dot3D rd = rotate_point({0, 0, 0}, d, {-r.angle_x, -r.angle_y, -r.angle_z});
        draw_dot(rd);
        for (dot3D d1 : dots_prepared) {
            int ex = d1.x == d.x;
            int ey = d1.y == d.y;
            int ez = d1.z == d.z;
            if (ex + ey + ez == 2) {
                dot3D rd1 = rotate_point({0, 0, 0}, d1, {-r.angle_x, -r.angle_y, -r.angle_z});
                draw_face(rd1, rd);
            }
        }
    }
}
