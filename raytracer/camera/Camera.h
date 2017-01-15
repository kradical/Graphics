#ifndef __CAMERA__
#define __CAMERA__

#include "../utility/Ray.h"

class Camera {
public:
    Vec3 origin;
    Vec3 lower_left_corner;
    Vec3 horizontal;
    Vec3 vertical;
    Vec3 u;
    Vec3 v;
    Vec3 w;
    float lens_radius;

    Camera(Vec3 from, Vec3 at, Vec3 up, float fov, float aspect, float aperture);
    
    Ray get_ray(float s, float t);
};

#endif
