#ifndef CAMERAH
#define CAMERAH

#include "ray.h"

vec3 random_in_unit_disk() {
    vec3 p;
    do {
        p = 2 * vec3(drand48(), drand48(), 0) - vec3(1, 1, 0);
    } while (dot(p, p) >= 1);
    return p;
}

class camera {
public:
    camera(vec3 from, vec3 at, vec3 up, float fov, float aspect, float aperture) {
        vec3 view = from - at;
        lens_radius = aperture / 2;
        origin = from;

        float theta = fov * M_PI / 180; // radians
        float height = 2 * tan(theta / 2);
        float width = aspect * height;
        float focus = view.length();

        w = unit_vector(view);
        u = unit_vector(cross(up, w));
        v = cross(w, u); // cross 2 unit vectors is a unit vector

        lower_left_corner = origin - (width / 2) * focus * u - (height / 2) * focus * v - focus * w;
        horizontal = width * focus * u;
        vertical = height * focus * v;
    }
    
    ray get_ray(float s, float t) { 
        vec3 rd = lens_radius * random_in_unit_disk();
        vec3 offset_origin = origin + u * rd.x() + v * rd.y();
        return ray(offset_origin, lower_left_corner + s * horizontal + t * vertical - offset_origin);
    }
    
    vec3 origin;
    vec3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
    vec3 u;
    vec3 v;
    vec3 w;
    float lens_radius;
};
#endif
