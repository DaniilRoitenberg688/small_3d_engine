#include <vector>

struct dot3D {
    float x;
    float y;
    float z;
};


struct dot2D {
    float x;
    float y;
};

struct face {
    dot3D start;
    dot3D end;
};
struct cube {
    dot3D center;
    float side;
    std::vector<dot3D> dots;
    std::vector<face> faces;
};
