#ifndef __MATERIAL__
#define __MATERIAL__

#include <cstdlib>
#include "../geometry/Hitable.h"
#include "../utility/Ray.h"


class Material {
public:
    virtual bool scatter(const Ray& r_in, const hit_record& rec, Vec3& attenuation, Ray& scattered) const = 0;

    Vec3 reflect(const Vec3& v, const Vec3& n) const;
    Vec3 random_in_unit_sphere() const;
};

#endif
