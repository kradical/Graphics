#ifndef __UTILS__
#define __UTILS__

#include "Ray.h"
#include "../geometry/HitableList.h"
#include "../light/PointLight.h"

Vec3 color(const Ray&, HitableList*, PointLight**, int);

#endif