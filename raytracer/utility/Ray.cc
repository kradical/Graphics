#include "Ray.h"

Ray::Ray() : origin(0.0), direction(0.0, 0.0, 1.0) {}
Ray::Ray(const Vec3& o, const Vec3& d) : origin(o), direction(d) {}
Ray::Ray(const Ray& ray) : origin(ray.origin), direction(ray.direction) {}

Ray& Ray::operator=(const Ray& rhs) {
    if (this == &rhs) {
        return (*this);
    }

    origin = rhs.origin; 
    direction = rhs.direction; 

    return (*this); 
}

Ray::~Ray() {}

Vec3 Ray::point_at(double d) const { return origin + d * direction; }
