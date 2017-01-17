#ifndef __RECT__
#define __RECT__

#include "Hitable.h"

class Material;

// Retangle: represented by 4 points.
// We assume that 4 points are planar.
//
//  a        b
//   +------+
//   |      |
//   |      |
//   +------+
//  d        c
class Rect: public Hitable {
public:
    Vec3 a, b, c, d;
    Vec3 u, v, n; // basis for the rect
    float minU, maxU;
    float minV, maxV;
    Material* mat_ptr;

    Rect(Vec3 _a, Vec3 _b, Vec3 _c, Vec3 _d, Material* m);

    virtual bool hit(const Ray& r, float tmin, float tmax, hit_record& rec) const;
};

#endif
