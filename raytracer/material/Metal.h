#ifndef __METAL__
#define __METAL__

#include "Material.h"

class Metal : public Material {
public:
    Vec3 surfaceColor;
    float fuzz;

    Metal(const Vec3& s, float f);
    
    virtual bool scatter(const Ray&, const hit_record&, Vec3&, Ray&) const;
    virtual Vec3 totalLitColor(PointLight**, hit_record*, HitableList*) const;
};

#endif
