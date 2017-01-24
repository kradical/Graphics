#include "Metal.h"
#include "../utility/Utils.h"

Metal::Metal(const Vec3& s, float f) : surfaceColor(s) { fuzz = f < 1 ? f : 1; }

bool Metal::scatter(const Ray& r_in, const hit_record& rec, Vec3& attenuation, Ray& scattered) const {
    Vec3 reflected = reflect(unit_vector(r_in.direction), rec.normal);
    scattered = Ray(rec.p, reflected + fuzz * random_in_unit_sphere());
    attenuation = surfaceColor;
    return dot(scattered.direction, rec.normal) > 0;
}

Vec3 Metal::totalLitColor(PointLight** lights, hit_record initialHit, HitableList* world, int depth) const {
    Vec3 reflected = reflect(unit_vector(initialHit.r_in.direction), initialHit.normal);
    Ray reflectedRay = Ray(initialHit.p, reflected + fuzz * random_in_unit_sphere());

    return surfaceColor * color(reflectedRay, world, lights, depth + 1);
}
