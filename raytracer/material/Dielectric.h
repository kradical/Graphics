#ifndef __DIELECTRIC__
#define __DIELECTRIC__

#include "Material.h"

class Dielectric : public Material { 
public:
    float ref_idx;
    Dielectric(float ri);
    
    virtual bool scatter(const Ray& r_in, const hit_record& rec, Vec3& attenuation, Ray& scattered) const;
    virtual Vec3 totalLitColor(PointLight** lights, hit_record initialHit, HitableList* world, int depth) const;
    bool refract(const Vec3& v, const Vec3& n, float ni_over_nt, Vec3& refracted) const;
    float schlick(float cosine, float ref_idx) const;
};

#endif
