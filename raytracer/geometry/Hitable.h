#ifndef __HITABLE__
#define __HITABLE__

#include "../utility/Ray.h"

class Material;

struct hit_record {
    float t; // how far along the ray
    Vec3 p; // point that was hit
    Vec3 normal;
    Material *mat_ptr;
};

class Hitable {
public:
    virtual bool hit(const Ray& r, float t_min, float t_max, hit_record& rec) const = 0;
};

#endif
