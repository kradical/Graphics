#include <iostream>
#include <stdlib.h>

#include "utility/Vec3.h"
#include "utility/Ray.h"
#include "camera/Camera.h"
#include "geometry/HitableList.h"
#include "geometry/Hitable.h"
#include "geometry/Sphere.h"
#include "geometry/Plane.h"
#include "material/Lambertian.h"
#include "material/Metal.h"
#include "material/Dielectric.h"
#include "float.h"

Vec3 color(const Ray&, Hitable*, int);
float hit_sphere(const Vec3&, float, const Ray&);
Hitable* scene();

int main() {
    int nx = 300; // width in pixels
    int ny = 150; // height in pixels
    int ns = 25; // number of samples per pixel
    
    Camera cam(Vec3(0, 0, 0), Vec3(0, 0, -1), Vec3(0, 1, 0), 90, float(nx) / float(ny), 0);
    Hitable* world = scene();

    std::cout << "P3\n" << nx << " " << ny << "\n255\n";
    for (int j = ny - 1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            Vec3 col(0, 0, 0);
            for (int s = 0; s < ns; s++) {
                float u = float(i + drand48()) / float(nx);
                float v = float(j + drand48()) / float(ny);
            
                Ray r = cam.get_ray(u, v);
            
                col += color(r, world, 0);
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
    int n = 4;
    Hitable** list = new Hitable*[n];
    list[0] = new Plane(Vec3(0, -0.5, 0), Vec3(0, 1, 0), new Lambertian(Vec3(0.8, 0.8, 0)));
    list[1] = new Sphere(Vec3(0, 0, -1), 0.5, new Lambertian(Vec3(0.1, 0.2, 0.5)));
    list[2] = new Sphere(Vec3(1, 0, -1), 0.5, new Metal(Vec3(0.5, 0.5, 0.5), 0));
    list[3] = new Sphere(Vec3(-1, 0, -1), -0.5, new Dielectric(1.1));

    return new HitableList(list, n);
}

Vec3 color(const Ray& r, Hitable* world, int depth) {
    hit_record rec;
    if (world->hit(r, 0.01, FLT_MAX, rec)) {
        Ray scattered;
        Vec3 attenuation;
        if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
            return attenuation * color(scattered, world, depth + 1);
        } else {
            return Vec3(0, 0, 0);
        }
    } else {
        // background
        Vec3 unit_direction = unit_vector(r.direction);
        float t = 0.5 * (unit_direction.y + 1.0);
        return (1 - t) * Vec3(1.0, 1.0, 1.0) + t * Vec3(0.5, 0.7, 1.0);
    }
}
