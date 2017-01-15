#include "Vec3.h"

Vec3::Vec3() {}
Vec3::Vec3(float e_all) { e[0] = e_all; e[1] = e_all; e[2] = e_all; }
Vec3::Vec3(float e0, float e1, float e2) { e[0] = e0; e[1] = e1; e[2] = e2; }
