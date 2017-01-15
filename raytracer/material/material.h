#ifndef MATERIALH
#define MATERIALH

class material {
public:
    virtual bool scatter(const Ray& r_in, const hit_record& rec, Vec3& attenuation, Ray& scattered) const = 0;

    Vec3 reflect(const Vec3& v, const Vec3& n) const {
        return v - 2 * dot(v, n) * n;
    }

    float schlick(float cosine, float ref_idx) const {
        float r0 = (1 - ref_idx) / (1 + ref_idx);
        r0 = r0 * r0;
        return r0 + (1 - r0) * pow((1 - cosine), 5);
    }

    bool refract(const Vec3& v, const Vec3& n, float ni_over_nt, Vec3& refracted) const {
        Vec3 uv = unit_vector(v);
        float dt = dot(uv, n);
        float discriminant = 1 - ni_over_nt * ni_over_nt * (1 - dt * dt);
        if (discriminant > 0) {
            refracted = ni_over_nt * (uv - n * dt) - n * sqrt(discriminant);
            return true;
        } else {
            return false;
        } 
    }
};

Vec3 random_in_unit_sphere() {
        Vec3 p;
        do {
            p = 2.0 * Vec3(drand48(), drand48(), drand48()) - Vec3(1, 1, 1);
        } while (dot(p, p) >= 1.0);
        return p;
    }
#endif
