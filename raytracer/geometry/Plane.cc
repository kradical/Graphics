#include "Plane.h"

Plane::Plane(Vec3 p, Vec3 n, Material* m) : p(p), n(n), mat_ptr(m) {};

bool Plane::hit(const Ray& r, float t_min, float t_max, hit_record& rec) const {
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
