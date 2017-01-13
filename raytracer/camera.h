#ifndef CAMERAH
#define CAMERAH

#include "ray.h"

class camera {
public:
    // simple ex:
    //   from = 0, 0, 0
    //   at = 0, 0, 1
    //   up = 0, 1, 0
    camera(vec3 from, vec3 at, vec3 up, float fov, float aspect) {
        origin = from;

        float theta = fov * M_PI / 180; // radians
        float height = 2 * tan(theta / 2);
        float width = aspect * height;

        vec3 w = unit_vector(from - at);
        vec3 u = unit_vector(cross(up, w));
        vec3 v = cross(w, u);

        lower_left_corner = vec3(-width / 2, -height / 2, -1);
        horizontal = vec3(width, 0, 0);
        vertical = vec3(0, height, 0);
    }
    
    ray get_ray(float s, float t) { 
        return ray(origin, lower_left_corner + s * horizontal + t * vertical - origin);
    }
    
    vec3 origin;
    vec3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
};
#endif
