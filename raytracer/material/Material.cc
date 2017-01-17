#include "Material.h"

Vec3 Material::reflect(const Vec3& v, const Vec3& n) const {
    return v - 2 * dot(v, n) * n;
}

Vec3 Material::random_in_unit_sphere() const {
    float x, y, z;
    do {
        x = 2.0 * drand48() - 1;
        y = 2.0 * drand48() - 1;
        z = 2.0 * drand48() - 1;
    } while (x * x + y * y + z * z > 1.0);
    return Vec3(x, y, z);
}
