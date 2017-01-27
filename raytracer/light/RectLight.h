#ifndef __RECTLIGHT__
#define __RECTLIGHT__

#include "../utility/Vec3.h"
#include "../geometry/Rect.h"

class PointLight {
public:
    Rect rect;
    Vec3 color;

    PointLight(Rect r, Vec3 c);
};

#endif
