#ifndef DIELECTRICH
#define DIELECTRICH

#include "material.h"

class dielectric : public material { 
    public:
        dielectric(float ri) : ref_idx(ri) {}
        
        virtual bool scatter(const Ray& r_in, const hit_record& rec, Vec3& attenuation, Ray& scattered) const  {
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

        float ref_idx;
};
#endif
