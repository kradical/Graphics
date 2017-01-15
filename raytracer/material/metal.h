#ifndef METALH
#define METALH

#include "material.h"

class metal : public material {
public:
    metal(const Vec3& a, float f) : albedo(a) { fuzz = f < 1 ? f : 1; }
    virtual bool scatter(const Ray& r_in, const hit_record& rec, Vec3& attenuation, Ray& scattered) const {
        Vec3 reflected = reflect(unit_vector(r_in.direction), rec.normal);
        scattered = Ray(rec.p, reflected + fuzz * random_in_unit_sphere());
        attenuation = albedo;
        return dot(scattered.direction, rec.normal) > 0;
    }
    
    Vec3 albedo;
    float fuzz;
};
#endif
