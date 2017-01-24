#include "Dielectric.h"
#include "../utility/Utils.h"

Dielectric::Dielectric(float ri) : ref_idx(ri) {}

bool Dielectric::scatter(const Ray& r_in, const hit_record& rec, Vec3& attenuation, Ray& scattered) const  {
    attenuation = Vec3(1.0, 1.0, 1.0);
    Vec3 outward_normal;
    Vec3 reflected = reflect(r_in.direction, rec.normal);
    Vec3 refracted;

    float ni_over_nt;
    float reflect_prob;
    float cosine;
    if (dot(r_in.direction, rec.normal) > 0) {
        outward_normal = -rec.normal;
        ni_over_nt = ref_idx;
        cosine = dot(r_in.direction, rec.normal) / r_in.direction.length();
        cosine = sqrt(1 - ref_idx*ref_idx*(1-cosine*cosine));
     } else {
        outward_normal = rec.normal;
        ni_over_nt = 1.0 / ref_idx;
        cosine = -dot(r_in.direction, rec.normal) / r_in.direction.length();
     }

    if (refract(r_in.direction, outward_normal, ni_over_nt, refracted)) {
        reflect_prob = schlick(cosine, ref_idx);
    } else {
        reflect_prob = 1.0;
    }
    if (drand48() < reflect_prob) {
        scattered = Ray(rec.p, reflected);
    } else  {
        scattered = Ray(rec.p, refracted);
    }
    
    return true;
}

bool Dielectric::refract(const Vec3& v, const Vec3& n, float ni_over_nt, Vec3& refracted) const {
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

float Dielectric::schlick(float cosine, float ref_idx) const {
    float r0 = (1 - ref_idx) / (1 + ref_idx);
    r0 = r0 * r0;
    return r0 + (1 - r0) * pow((1 - cosine), 5);
}

Vec3 Dielectric::totalLitColor(PointLight** lights, hit_record initialHit, HitableList* world, int depth) const {
    Vec3 outward_normal;
    Vec3 reflected = reflect(initialHit.r_in.direction, initialHit.normal);
    Vec3 refracted;

    float ni_over_nt;
    float reflect_prob;
    float cosine;
    if (dot(initialHit.r_in.direction, initialHit.normal) > 0) {
        outward_normal = -initialHit.normal;
        ni_over_nt = ref_idx;
        cosine = dot(initialHit.r_in.direction, initialHit.normal) / initialHit.r_in.direction.length();
        cosine = sqrt(1 - ref_idx * ref_idx * (1 - cosine * cosine));
     } else {
        outward_normal = initialHit.normal;
        ni_over_nt = 1.0 / ref_idx;
        cosine = -dot(initialHit.r_in.direction, initialHit.normal) / initialHit.r_in.direction.length();
     }

    if (refract(initialHit.r_in.direction, outward_normal, ni_over_nt, refracted)) {
        reflect_prob = schlick(cosine, ref_idx);
    } else {
        reflect_prob = 1.0;
    }

    Ray r;
    if (drand48() < reflect_prob) {
        r = Ray(initialHit.p, reflected);
    } else  {
        r = Ray(initialHit.p, refracted);
    }

    return color(r, world, lights, depth + 1);
}
