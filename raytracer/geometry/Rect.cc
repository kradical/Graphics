#include "Rect.h"

#include <iostream>
#include <cmath>

inline float min(float a, float b, float c, float d) {
    float min_ab, min_bc;
    min_ab = a < b ? a : b;
    min_bc = c < d ? b : c;
    return min_ab < min_bc ? min_ab : min_bc;
}

inline float max(float a, float b, float c, float d) {
    float max_ab, max_bc;
    max_ab = a > b ? a : b;
    max_bc = c > d ? b : c;
    return max_ab > max_bc ? max_ab : max_bc;
}

Rect::Rect(Vec3 _a, Vec3 _b, Vec3 _d, Material* m) : a(_a), b(_b), d(_d), mat_ptr(m) {
    u = unit_vector(b - a);
    v = unit_vector(d - a);
    n = cross(u, v); // cross 2 unit vecs is a unit vec

    c = b + d - a; // a + (b - a) + (d - a)

    float ua = dot(u, a);
    float ub = dot(u, b);
    float uc = dot(u, c);
    float ud = dot(u, d);

    minU = min(ua, ub, uc, ud);
    maxU = max(ua, ub, uc, ud);

    float va = dot(v, a);
    float vb = dot(v, b);
    float vc = dot(v, c);
    float vd = dot(v, d);

    minV = min(va, vb, vc, vd);
    maxV = max(va, vb, vc, vd);
};

bool Rect::hit(const Ray& r, float t_min, float t_max, hit_record& rec) const {
    float normal_component = dot(n, r.direction);

    // ray hits plane in scene (some component is opposite)
    if (normal_component != 0) {
        float t = dot(n, a - r.origin) / normal_component;
        // if point hit is between eye and where we are so far
        if (t < t_max && t > t_min) {
            float u_comp = dot(u, r.point_at(t));
            float v_comp = dot(v, r.point_at(t));

            if (u_comp > minU && u_comp < maxU &&
                v_comp > minV && v_comp < maxV) {

                rec.t = t;
                rec.p = r.point_at(rec.t);
                rec.normal = n;
                rec.r_in = r;
                rec.mat_ptr = mat_ptr;

                return true;
            }
        }
    }

    return false;
}
