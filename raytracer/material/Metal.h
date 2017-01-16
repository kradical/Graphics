#ifndef __METAL__
#define __METAL__

#include "Material.h"

class Metal : public Material {
public:
    Vec3 albedo;
    float fuzz;

    Metal(const Vec3& a, float f);
    
    virtual bool scatter(const Ray& r_in, const hit_record& rec, Vec3& attenuation, Ray& scattered) const;
};

#endif
