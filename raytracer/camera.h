#ifndef CAMERAH
#define CAMERAH

#include <iostream>
using namespace std;
#include "ray.h"

class camera {
public:
    camera(vec3 from, vec3 at, vec3 up, float fov, float aspect) {
        // othonormal basis for camera
        // w points into camera
        vec3 u, v, w;

        w = unit_vector(from - at);
        u = unit_vector(cross(up, w));
        v = unit_vector(cross(w, u));
        origin = from;

        float theta = fov * M_PI / 180; // radians
        float half_height = tan(theta / 2);
        float half_width = aspect * half_height;



        lower_left_corner = vec3(-half_width, -half_height, -1);
        horizontal = 2 * half_width * u;
        vertical = 2 * half_height * v;
    }
    
    ray get_ray(float u, float v) { 
        return ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
    }
    
    vec3 origin;
    vec3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
};
#endif
