#ifndef __RAY__
#define __RAY__

#include "Vec3.h"

class Ray {

public:
    Vec3 origin;
    Vec3 direction;

    Ray(void); // default
    Ray(const Vec3& o, const Vec3& d); // constructor
    Ray(const Ray& ray); // copy
    Ray& operator=(const Ray& rhs);
    ~Ray();
    Vec3 point_at(double d) const;
};
#endif
