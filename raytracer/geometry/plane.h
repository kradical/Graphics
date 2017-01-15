#ifndef PLANEH
#define PLANEH

#include "hitable.h"

class material;

// plane: represented by a point and a normal
class plane: public hitable {
public:
    plane() {}
    plane(Vec3 p, Vec3 n, material* m) : p(p), n(n), mat_ptr(m) {};

    virtual bool hit(const Ray& r, float tmin, float tmax, hit_record& rec) const;

    Vec3 p;
    Vec3 n;
    material* mat_ptr;
};

bool plane::hit(const Ray& r, float t_min, float t_max, hit_record& rec) const {
    float normal_component = dot(n, r.direction);

    // ray hits plane in scene (some component is opposite)
    if (normal_component != 0) {
        float t = dot(n, p - r.origin) / normal_component;
        // if point hit is between eye and where we are so far
        if (t < t_max && t > t_min) {
            rec.t = t;
            rec.p = r.point_at(rec.t);
            rec.normal = n;
            rec.mat_ptr = mat_ptr;

            return true;
        }
    }

    return false;
}
#endif
