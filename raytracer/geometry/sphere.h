#ifndef SPHEREH
#define SPHEREH

#include "hitable.h"

class material;

class sphere: public hitable {
public:
    sphere() {}
    sphere(Vec3 cen, float r, material* m) : center(cen), radius(r), mat_ptr(m) {};

    virtual bool hit(const Ray& r, float tmin, float tmax, hit_record& rec) const;

    Vec3 center;
    float radius;
    material* mat_ptr;
};

bool sphere::hit(const Ray& r, float t_min, float t_max, hit_record& rec) const {
    Vec3 oc = r.origin - center;

    float a = dot(r.direction, r.direction);
    float b = dot(oc, r.direction);
    float c = dot(oc, oc) - radius * radius;
    float discriminant = b * b - a * c;
    if (discriminant > 0) {
        // first root
        float temp = (-b - sqrt(discriminant)) / a;
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.point_at(rec.t);
            rec.normal = (rec.p - center) / radius;
            rec.mat_ptr = mat_ptr;
            return true;
        }

        // second root
        temp = (-b + sqrt(discriminant)) / a;
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.point_at(rec.t);
            rec.normal = (rec.p - center) / radius;
            rec.mat_ptr = mat_ptr;
            return true;
        }
    }

    return false;
}
#endif