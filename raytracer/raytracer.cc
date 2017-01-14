#include <iostream>
#include <stdlib.h>

#include "vec3.h"
#include "ray.h"
#include "hitable.h"
#include "camera.h"
#include "sphere.h"
#include "plane.h"
#include "lambertian.h"
#include "metal.h"
#include "dielectric.h"
#include "hitable_list.h"
#include "float.h"

vec3 color(const ray&, hitable*, int);
float hit_sphere(const vec3&, float, const ray&);
hitable* scene();

int main() {
    int nx = 400; // width in pixels
    int ny = 200; // height in pixels
    int ns = 25; // number of samples per pixel
    
    camera cam(vec3(0, 0, 0), vec3(0, 0, -1), vec3(0, 1, 0), 90, float(nx) / float(ny), 0);
    hitable* world = scene();

    std::cout << "P3\n" << nx << " " << ny << "\n255\n";
    for (int j = ny - 1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            vec3 col(0, 0, 0);
            for (int s = 0; s < ns; s++) {
                float u = float(i + drand48()) / float(nx);
                float v = float(j + drand48()) / float(ny);
            
                ray r = cam.get_ray(u, v);
            
                col += color(r, world, 0);
            }

            col /= float(ns);
            
            col = vec3(sqrt(col.r()), sqrt(col.g()), sqrt(col.b()));

            int ir = int(255.99 * col.r());
            int ig = int(255.99 * col.g());
            int ib = int(255.99 * col.b());

            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }
}

hitable* scene() {
    int n = 4;
    hitable** list = new hitable*[n];
    list[0] = new plane(vec3(0, -0.5, 0), vec3(0, 1, 0), new lambertian(vec3(0.8, 0.8, 0)));
    list[1] = new sphere(vec3(0, 0, -1), 0.5, new lambertian(vec3(0.1, 0.2, 0.5)));
    list[2] = new sphere(vec3(1, 0, -1), 0.5, new metal(vec3(0.5, 0.5, 0.5), 0));
    list[3] = new sphere(vec3(-1, 0, -1), -0.5, new dielectric(1.1));

    return new hitable_list(list, n);
}

vec3 color(const ray& r, hitable* world, int depth) {
    hit_record rec;
    if (world->hit(r, 0.01, FLT_MAX, rec)) {
        ray scattered;
        vec3 attenuation;
        if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
            return attenuation * color(scattered, world, depth + 1);
        } else {
            return vec3(0, 0, 0);
        }
    } else {
        // background
        vec3 unit_direction = unit_vector(r.direction);
        float t = 0.5 * (unit_direction.y() + 1.0);
        return (1 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
    }
}
