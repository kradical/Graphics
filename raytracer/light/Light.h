#ifndef __LIGHT__
#define __LIGHT__

#include "../utility/Ray.h"

class Hitable {
public:
    virtual bool hit(const Ray& r, float t_min, float t_max, hit_record& rec) const = 0;
};

#endif
