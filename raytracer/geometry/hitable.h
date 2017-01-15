#ifndef HITABLEH
#define HITABLEH

#include "../utility/Ray.h"

class material;

struct hit_record {
    float t;
    Vec3 p;
    Vec3 normal;
    material *mat_ptr;
};

class hitable {
public:
    virtual bool hit(const Ray& r, float t_min, float t_max, hit_record& rec) const = 0;
};
#endif
