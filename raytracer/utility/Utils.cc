#include "Utils.h"
#include "../geometry/Hitable.h"
#include "../material/Material.h"
#include "Vec3.h"
#include "float.h"

Vec3 color(const Ray& r, HitableList* world, PointLight** lights, int depth) {
    hit_record rec;

    Vec3 backgroundColor = Vec3(0, 0, 1);
    
    if (world->hit(r, 0.01, FLT_MAX, rec)) {
        hit_record initialHit = rec;

        Vec3 surfaceColor = Vec3();
        Ray scattered = Ray();
        if (depth < 2 && rec.mat_ptr->scatter(r, rec, surfaceColor, scattered)) {
            Vec3 totalColor = (rec.mat_ptr->totalLitColor(lights, &initialHit, world) + 0.1 * color(scattered, world, lights, depth + 1)) / 1.1;
            return totalColor;
        } else {
            return Vec3(0);
        }
    } else {
        return backgroundColor;
    }
}
