#ifndef __LAMBERTIAN__
#define __LAMBERTIAN__

#include "Material.h"

class Lambertian : public Material {
public:
    Vec3 albedo;

    Lambertian(const Vec3& a);
    
    virtual bool scatter(const Ray& r_in, const hit_record& rec, Vec3& attenuation, Ray& scattered) const;
};

#endif
