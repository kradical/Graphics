#include "Material.h"

Vec3 Material::reflect(const Vec3& v, const Vec3& n) const {
    return v - 2 * dot(v, n) * n;
}

Vec3 Material::random_in_unit_sphere() const {
    Vec3 p;
    do {
        p = 2.0 * Vec3(drand48(), drand48(), drand48()) - Vec3(1, 1, 1);
    } while (p.squared_length() >= 1.0);
    return p;
}
