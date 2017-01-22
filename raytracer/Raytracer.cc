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

Vec3 color(const Ray&, Hitable*, PointLight**, int);
float hit_sphere(const Vec3&, float, const Ray&);
Hitable* scene();
PointLight** scene_lighting();

int main() {
    int nx = 800; // width in pixels
    int ny = 600; // height in pixels
    int ns = 5; // number of samples per pixel
    
    Camera cam(Vec3(-2, 2, 1), Vec3(0, 0, -1), Vec3(0, 1, 0), 90, float(nx) / float(ny), 0.1);
    Hitable* world = scene();
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

Hitable* scene() {
    int n = 3;
    Hitable** list = new Hitable*[n];
    list[0] = new Plane(Vec3(0, -1, 0), Vec3(0, 1, 0), new Lambertian(Vec3(1, 0, 0)));
    //list[1] = new Plane(Vec3(-10, 0, 0), Vec3(1, 0, 0), new Lambertian(Vec3(0.5, 0.1, 0.1)));
    // list[0] = new Rect(Vec3(-2.5, 1, -3.5), Vec3(2.5, -1, -3.5), Vec3(-2.5, 1, 1.5), new Lambertian(Vec3(0.8, 0.8, 0)));
    list[1] = new Sphere(Vec3(0, 0, -1), 0.5, new Lambertian(Vec3(0.01, 1, 0.01)));
    list[2] = new Sphere(Vec3(1, 0, -1), 0.5, new Lambertian(Vec3(0.01, 0.01, 1)));

    return new HitableList(list, n);
}

#define NUM_LIGHTS 1
PointLight** scene_lighting() {
    PointLight** list = new PointLight*[NUM_LIGHTS];
    //list[0] = new PointLight(Vec3(1, 1, 0), Vec3(1), 1);
    list[0] = new PointLight(Vec3(0, 1, -1), Vec3(1), 1);

    return list;
}

Vec3 color(const Ray& r, Hitable* world, PointLight** lights, int depth) {
    hit_record rec;
    if (world->hit(r, 0.01, FLT_MAX, rec)) {
        hit_record initialHit = rec; // TODO remove this once looping thru hitlist.
        
        Vec3 totalColor = Vec3(0);
        int lightsHit = 0;

        Vec3 surfaceColor = Vec3();
        Ray scattered = Ray();
        rec.mat_ptr->scatter(r, rec, surfaceColor, scattered);
        
        for (int i = 0; i < NUM_LIGHTS; i++){
            Ray lightDirection = Ray(initialHit.p + 1e-4 * initialHit.normal, unit_vector(lights[i]->point - initialHit.p));

            // TODO: fix this to take light location into consideration and be a quick exiting loop
            if (!world->hit(lightDirection, 0.01, FLT_MAX, rec)) {
                lightsHit += 1;
                totalColor += (surfaceColor * lights[i]->color) * lights[i]->intensity * std::max(float(0), dot(initialHit.normal, lightDirection.direction));;
            }
        }
    
        if (lightsHit > 1) {
            totalColor /= lightsHit;
        }
        return totalColor;
    } else {
        return Vec3(0.1, 0.1, 0.5);
    }
}
