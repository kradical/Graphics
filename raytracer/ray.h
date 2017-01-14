#ifndef RAYH
#define RAYH
#include "vec3.h"

class ray {

public:
    ray() {}
    ray(const vec3& a, const vec3& b) { origin = a; direction = b; }
    
    // point at parameter d (line = P + dL)
    vec3 point_at(float d) const { return origin + d * direction; }

    vec3 origin;
    vec3 direction;
};
#endif
