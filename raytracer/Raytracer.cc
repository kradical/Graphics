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
#include "utility/Utils.h"

Vec3 color(const Ray&, HitableList*, PointLight**, int);
float hit_sphere(const Vec3&, float, const Ray&);
HitableList* scene();
PointLight** scene_lighting();

int main() {
    int nx = 600; // width in pixels
    int ny = 400; // height in pixels
    int ns = 5; // number of samples per pixel
    
    Camera cam(Vec3(0, 0.5, 1), Vec3(0, 0, -1), Vec3(0, 1, 0), 90, float(nx) / float(ny), 0.01);
    HitableList* world = scene();
    PointLight** lights = scene_lighting();

    std::cout << "P3\n" << nx << " " << ny << "\n255\n";
    for (int j = ny - 1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            Vec3 col(0);
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
    int n = 5;
    Hitable** list = new Hitable*[n];
    list[0] = new Sphere(Vec3(0, 0, -1), 0.5, new Lambertian(Vec3(0.1, 0.6, 0.6)));
    list[1] = new Sphere(Vec3(1.1, 0, -1), 0.5, new Metal(Vec3(0.5, 0.5, 0.5), 0.1));
    list[2] = new Rect(Vec3(1.6, -0.5, -2), Vec3(-1.6, -0.5, -2), Vec3(1.6, -0.5, 0), new Lambertian(Vec3(1, 0, 0)));
    list[3] = new Rect(Vec3(-1.6, 2, -4), Vec3(-1.6, 2, 0), Vec3(1.6, 0, -4), new Lambertian(Vec3(0, 1, 0)));

    int dielectrics = 1;
    list[4] = new Sphere(Vec3(-1.1, 0, -1), 0.5, new Dielectric(1.1));
    return new HitableList(list, n, n - dielectrics);
}

// TODO: add a light list type
PointLight** scene_lighting() {
    PointLight** list = new PointLight*[1];
    list[0] = new PointLight(Vec3(1, 1, 1), Vec3(1));
    list[1] = new PointLight(Vec3(0, 0.5, -1), Vec3(0.1)); // small light at camera

    return list;
}
