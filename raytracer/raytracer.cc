#include <iostream>
#include <stdlib.h>

#include "camera.h"
#include "hitable_list.h"
#include "sphere.h"
#include "lambertian.h"
#include "metal.h"
#include "dielectric.h"
#include "float.h"

vec3 color(const ray&, hitable*, int);
float hit_sphere(const vec3&, float, const ray&);

int main() {
    int nx = 200;
    int ny = 100;
    int ns = 100;
    
    camera cam(vec3(0, 0, 1), vec3(0, 0, -1), vec3(0, 1, 0), 90, float(nx) / float(ny));

    hitable* list[4];
    list[0] = new sphere(vec3(0, 0, -1), 0.5, new lambertian(vec3(0.1, 0.2, 0.5)));
    list[1] = new sphere(vec3(0, -100.6, -1), 100, new lambertian(vec3(0.8, 0.8, 0.0)));
    list[2] = new sphere(vec3(1, 0, -1), 0.5, new metal(vec3(0.8, 0.6, 0.2), 0.3));
    list[3] = new sphere(vec3(-1, 0, -1), -0.5, new dielectric(1.5));

    hitable* world = new hitable_list(list, 4);

    std::cout << "P3\n" << nx << " " << ny << "\n255\n";
    for (int j = ny - 1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            vec3 col(0, 0, 0);
            for (int s = 0; s < ns; s++) {
                float u = float(i + drand48()) / float(nx);
                float v = float(j + drand48()) / float(ny);
            
                ray r = cam.get_ray(u, v);
            
                vec3 p = r.point_at_parameter(2.0);
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
        vec3 unit_direction = unit_vector(r.direction);
        float t = 0.5 * (unit_direction.y() + 1.0);
        return (1 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
    }
}
