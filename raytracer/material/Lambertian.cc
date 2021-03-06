#include "Lambertian.h"
#include <iostream>

Lambertian::Lambertian(const Vec3& s) : surfaceColor(s) {}

bool Lambertian::scatter(const Ray& r_in, const hit_record& rec, Vec3& attenuation, Ray& scattered) const {
    Vec3 target = rec.p + rec.normal + random_in_unit_sphere();
    scattered = Ray(rec.p, target - rec.p);
    attenuation = surfaceColor;
    return true;
}

Vec3 Lambertian::totalLitColor(PointLight** lights, hit_record initialHit, HitableList* world, int depth) const {
    hit_record rec;

    Vec3 totalColor = Vec3(0);

    int numLights = 3;
    for (int i = 0; i < numLights; i++){
        Vec3 toLight = lights[i]->point - initialHit.p;
        Ray lightDirection = Ray(initialHit.p + 1e-4 * initialHit.normal, unit_vector(toLight));

        bool hit_nothing = true;
        for (int j = 0; j < world->non_dielectrics; j++) {
            if(world->list[j]->hit(lightDirection, 0.01, toLight.length(), rec)) {
                hit_nothing = false;
                break;
            }
        }

        if (hit_nothing) {
            totalColor += (surfaceColor * lights[i]->color) * std::max(float(0), dot(initialHit.normal, lightDirection.direction));
        }
    }

    return totalColor;
}
