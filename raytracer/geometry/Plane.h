#ifndef __PLANE__
#define __PLANE__

#include "Hitable.h"

class Material;

// plane: represented by a point and a normal
class Plane: public Hitable {
public:
    Vec3 p;
    Vec3 n;
    Material* mat_ptr;

    Plane(Vec3 p, Vec3 n, Material* m);

    virtual bool hit(const Ray& r, float tmin, float tmax, hit_record& rec) const;
};

#endif
