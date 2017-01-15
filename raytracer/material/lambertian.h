#ifndef LAMBERTIANH
#define LAMBERTIANH

#include "material.h"

class lambertian : public material {
public:
    lambertian(const Vec3& a) : albedo(a) {}
    virtual bool scatter(const Ray& r_in, const hit_record& rec, Vec3& attenuation, Ray& scattered) const {
        Vec3 target = rec.p + rec.normal + random_in_unit_sphere();
        scattered = Ray(rec.p, target - rec.p);
        attenuation = albedo;
        return true;
    }
    
    Vec3 albedo;
};
#endif
