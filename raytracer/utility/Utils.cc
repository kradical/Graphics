#include "Utils.h"
#include "../geometry/Hitable.h"
#include "../material/Material.h"
#include "Vec3.h"
#include "float.h"

Vec3 color(const Ray& r, HitableList* world, PointLight** lights, int depth) {
    hit_record rec;

    Vec3 backgroundColor = Vec3(0);
    
    if (world->hit(r, 0.01, FLT_MAX, rec)) {
        hit_record initialHit = rec;

        Vec3 temp;
        Ray scattered = Ray();
        if (depth < 5 && rec.mat_ptr->scatter(r, rec, temp, scattered)) {
            Vec3 totalColor = (rec.mat_ptr->totalLitColor(lights, initialHit, world, depth) + 0.1 * color(scattered, world, lights, depth + 1)) / 1.1;
            return totalColor;
        } else {
            return Vec3(0);
        }
    } else {
        return backgroundColor;
    }
}
