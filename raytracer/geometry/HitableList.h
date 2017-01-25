#ifndef __HITABLELIST__
#define __HITABLELIST__

#include "Hitable.h"

class HitableList: public Hitable {
public:
    Hitable** list;
    int list_size;
    int non_dielectrics;

    HitableList(Hitable** l, int n, int nd);

    virtual bool hit(const Ray& r, float tmin, float tmax, hit_record& rec) const;
};

#endif
