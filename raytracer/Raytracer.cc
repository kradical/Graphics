#include <iostream>
#include <stdlib.h>

#include "utility/Vec3.h"
#include "utility/Ray.h"
#include "camera/Camera.h"
#include "geometry/HitableList.h"
#include "geometry/Hitable.h"
#include "geometry/Sphere.h"
#include "geometry/Plane.h"
#include "geometry/Rect.h"
#include "material/Lambertian.h"
#include "material/Metal.h"
#include "material/Dielectric.h"
#include "light/PointLight.h"
#include "float.h"

Vec3 color(const Ray&, HitableList*, PointLight**, int);
Vec3 totalLitColor(HitableList*, PointLight**, hit_record*, Vec3*);
float hit_sphere(const Vec3&, float, const Ray&);
HitableList* scene();
PointLight** scene_lighting();

int main() {
    int nx = 800; // width in pixels
    int ny = 600; // height in pixels
    int ns = 10; // number of samples per pixel
    
    Camera cam(Vec3(0, 1, 1), Vec3(0, 0, -1), Vec3(0, 1, 0), 90, float(nx) / float(ny), 0.01);
    HitableList* world = scene();
    PointLight** lights = scene_lighting();

    std::cout << "P3\n" << nx << " " << ny << "\n255\n";
    for (int j = ny - 1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            Vec3 col(0, 0, 0);
            for (int s = 0; s < ns; s++) {
                float u = float(i + drand48()) / float(nx);
                float v = float(j + drand48()) / float(ny);
            
                Ray r = cam.get_ray(u, v);
            
                col += color(r, world, lights, 0);
            }

            col /= float(ns);
            
            col = Vec3(sqrt(col.x), sqrt(col.y), sqrt(col.z));

            int ir = int(255.99 * col.x);
            int ig = int(255.99 * col.y);
            int ib = int(255.99 * col.z);

            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }
}

HitableList* scene() {
    int n = 4;
    Hitable** list = new Hitable*[n];
    list[0] = new Plane(Vec3(0, -1, 0), Vec3(0, 1, 0), new Lambertian(Vec3(1, 0, 0)));
    list[1] = new Sphere(Vec3(0, 0, -1), 0.5, new Lambertian(Vec3(0.01, 1, 0.01)));
    list[2] = new Sphere(Vec3(1, 0, -1), 0.5, new Lambertian(Vec3(0.01, 0.01, 1)));
    list[3] = new Plane(Vec3(4, 0, 0), Vec3(-1, 0, 0), new Lambertian(Vec3(0, 1, 0)));

    return new HitableList(list, n);
}

#define NUM_LIGHTS 1
PointLight** scene_lighting() {
    PointLight** list = new PointLight*[NUM_LIGHTS];
    list[0] = new PointLight(Vec3(-1, 1, 0), Vec3(1));
    list[1] = new PointLight(Vec3(0, 0, 0), Vec3(0.01)); // small light at camera

    return list;
}

Vec3 color(const Ray& r, HitableList* world, PointLight** lights, int depth) {
    hit_record rec;
    
    if (world->hit(r, 0.01, FLT_MAX, rec)) {
        hit_record initialHit = rec;

        Vec3 surfaceColor = Vec3();
        Ray scattered = Ray();
        if (depth < 2 && rec.mat_ptr->scatter(r, rec, surfaceColor, scattered)) {
            Vec3 totalColor = (totalLitColor(world, lights, &initialHit, &surfaceColor) + 0.1 * color(scattered, world, lights, depth + 1)) / 1.1;
            return totalColor;
        } else {
            return Vec3(0);
        }
    } else {
        return Vec3(0);
    }
}

Vec3 totalLitColor(HitableList* world, PointLight** lights, hit_record* initialHit, Vec3* surfaceColor) {
    hit_record rec;

    Vec3 totalColor = Vec3(0);
    int lightsHit = 0;

    for (int i = 0; i < NUM_LIGHTS; i++){
        Vec3 toLight = lights[i]->point - initialHit->p;
        Ray lightDirection = Ray(initialHit->p + 1e-4 * initialHit->normal, unit_vector(toLight));

        bool hit_anything = true;
        for (int j = 0; j < world->list_size; j++) {
            if(world->list[j]->hit(lightDirection, 0.01, toLight.length(), rec)) {
                hit_anything = false;
                break;
            }
        }

        if (hit_anything) {
            lightsHit += 1;
            totalColor += (*surfaceColor * lights[i]->color) * std::max(float(0), dot(initialHit->normal, lightDirection.direction));;
        }
    }

    if (lightsHit > 1) {
        totalColor /= lightsHit;
    }

    return totalColor;
}
