#include "Camera.h"
#include <cstdlib>

Vec3 random_in_unit_disk() {
    Vec3 p;
    do {
        p = 2 * Vec3(drand48(), drand48(), 0) - Vec3(1, 1, 0);
    } while (p.squared_length() >= 1);
    return p;
}

Camera::Camera(Vec3 from, Vec3 at, Vec3 up, float fov, float aspect, float aperture) {
    Vec3 view = from - at;
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

Ray Camera::get_ray(float s, float t) { 
    Vec3 rd = lens_radius * random_in_unit_disk();
    Vec3 offset_origin = origin + u * rd.x + v * rd.y;
    return Ray(offset_origin, lower_left_corner + s * horizontal + t * vertical - offset_origin);
}
