#ifndef __SPHERE__
#define __SPHERE__

#include "Hitable.h"

class Material;

class Sphere: public Hitable {
public:
    Vec3 center;
    float radius;
    Material* mat_ptr;

    Sphere(Vec3 cen, float r, Material* m);

    virtual bool hit(const Ray& r, float tmin, float tmax, hit_record& rec) const;
};

#endif
