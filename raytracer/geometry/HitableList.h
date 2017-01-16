#ifndef __HITABLELIST__
#define __HITABLELIST__

#include "Hitable.h"

class HitableList: public Hitable {
public:
    Hitable** list;
    int list_size;

    HitableList(Hitable** l, int n);

    virtual bool hit(const Ray& r, float tmin, float tmax, hit_record& rec) const;
};

#endif
