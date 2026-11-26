#include "cube.h"
#include "dots.h"
#include "faces.h"
#include "rotation.h"
#include <cmath>

const float near = 0.2f;

bool float_equal(float a, float b) {
    const float epsilon = 1e-5f;
    return std::fabs(a - b) < epsilon;
}

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

dot3D prepare_dot_for_calculations(dot3D d, dot3D c_center) {

    return {
          d.x + c_center.x,
          d.y + c_center.y,
          d.z + c_center.z
    };
}

dot3D prepare_dot_for_showing(dot3D d, dot3D camera, rotation r) {

    return rotate_point({0, 0, 0},{
        d.x - camera.x,
        d.y - camera.y,
        d.z - camera.z}, {-r.angle_x, -r.angle_y, -r.angle_z});
}

void draw_cube(cube c, dot3D camera, rotation r) {
    // std::vector<dot3D> dots_prepared = prepare_cube_for_drawing(c, camera);
    dot3D rotation_center = {0, 0, 0};
    int counter = 0;
    for (dot3D d : c.dots) {
        dot3D calcaulation_d = prepare_dot_for_calculations(d, c.center);
        bool can_be_seen_d = check_if_dot_can_be_seen(calcaulation_d, camera, r);
        dot3D rd = prepare_dot_for_showing(calcaulation_d, camera, r);
        can_be_seen_d = can_be_seen_d && rd.z > near;
        if (can_be_seen_d) {
            draw_dot(rd);

        }
        for (dot3D d1 : c.dots) {
            int ex = float_equal(d1.x, d.x);
            int ey = float_equal(d1.y, d.y);
            int ez = float_equal(d1.z, d.z);
            if (ex + ey + ez == 2) {
                counter++;
                dot3D calcaulation_d1 = prepare_dot_for_calculations(d1, c.center);
                bool can_be_seen_d1 = check_if_dot_can_be_seen(calcaulation_d1, camera, r);
                dot3D rd1 = prepare_dot_for_showing(calcaulation_d1, camera, r);
                can_be_seen_d1 = can_be_seen_d1 && rd1.z > near;
                if (can_be_seen_d && can_be_seen_d1) {
                    // std::cout << d.x << " " << d.y << " " << d.z << "\n";
                    // std::cout << d1.x << " " << d1.y << " " << d1.z << "\n";
                    draw_face(rd1, rd);
                } else if (can_be_seen_d) {
                    dot3D new_dot = intersect_surface_and_line(calcaulation_d, calcaulation_d1, r, camera);
                    dot3D rd1 = prepare_dot_for_showing(new_dot, camera, r);
                    draw_face(rd1, rd);
                } else if (can_be_seen_d1) {
                    dot3D new_dot = intersect_surface_and_line(calcaulation_d, calcaulation_d1, r, camera);
                    dot3D rd = prepare_dot_for_showing(new_dot, camera, r);
                    dot3D rd1 = prepare_dot_for_showing(calcaulation_d1, camera, r);
                    draw_face(rd1, rd);
                }
            }
        }
    }
    // std::cout << counter << "\n";

}

dot3D intersect_surface_and_line(dot3D d1, dot3D d2, rotation r, dot3D cd) {
    dot3D f = {0, 0, 1};
    dot3D rf = rotate_point({0, 0, 0}, f, r);
    float c_x = rf.x;
    float c_y = rf.y;
    float c_z = rf.z;
    float D = cd.x * c_x + cd.y * c_y + cd.z * c_z + near;
    float a = (d2.x - d1.x);
    float b = (d2.y - d1.y);
    float c = (d2.z - d1.z);

    float t = (D - c_x * d1.x - c_y * d1.y - c_z * d1.z ) / (c_x * a + c_y * b + c_z * c);
    return {
    d1.x + a * t,
    d1.y + b * t,
    d1.z + c * t,
    };
}

bool check_if_dot_can_be_seen(dot3D d, dot3D cd, rotation c_r) {
    dot3D f = {0, 0, 1};
    dot3D rf = rotate_point({0, 0, 0}, f, c_r);
    float c_x = rf.x;
    float c_y = rf.y;
    float c_z = rf.z;

    float a = d.x - cd.x;
    float b = d.y - cd.y;
    float c = d.z - cd.z;

    float p = a * c_x + b * c_y + c * c_z;
    return p > near;
}
