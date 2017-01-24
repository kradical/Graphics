#ifndef __LAMBERTIAN__
#define __LAMBERTIAN__

#include "Material.h"

class Lambertian : public Material {
public:
    Vec3 surfaceColor;

    Lambertian(const Vec3& s);
    
    virtual bool scatter(const Ray& r_in, const hit_record& rec, Vec3& attenuation, Ray& scattered) const;
    virtual Vec3 totalLitColor(PointLight** lights, hit_record initialHit, HitableList* world, int depth) const;
};

#endif
