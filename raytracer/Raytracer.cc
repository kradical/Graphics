#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

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
    int width = 1024; // width in pixels
    int height = 768; // height in pixels
    int samples = 25; // number of samples per pixel

    unsigned char pixels[height * width][4];
    
    Camera cam(Vec3(0, 0.5, 2), Vec3(1, 0, -1), Vec3(0, 1, 0), 90, float(width) / float(height), 0.05);
    HitableList* world = scene();
    PointLight** lights = scene_lighting();

    #pragma omp parallel for
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            Vec3 col(0);
            for (int s = 0; s < samples; s++) {
                float u = float(i + drand48()) / float(width);
                float v = float(height - j + drand48()) / float(height);
            
                Ray r = cam.get_ray(u, v);
            
                col += color(r, world, lights, 0);
            }

            col /= float(samples);

            pixels[j * width + i][0] = int(255.99 * sqrt(col.x));
            pixels[j * width + i][1] = int(255.99 * sqrt(col.y));
            pixels[j * width + i][2] = int(255.99 * sqrt(col.z));
            pixels[j * width + i][3] = 255;
        }
    }

    stbi_write_png("raytrace.png", width, height, 4, pixels, width * 4);
}

HitableList* scene() {
    int n = 7;
    Hitable** list = new Hitable*[n];
    list[0] = new Sphere(Vec3(0, 0, -1.1), 0.5, new Lambertian(Vec3(1)));
    list[1] = new Sphere(Vec3(-1, 0, -1), 0.5, new Lambertian(Vec3(1)));
    list[2] = new Rect(Vec3(3.1, -0.5, -2), Vec3(-2.6, -0.5, -2), Vec3(3.1, -0.5, 0), new Lambertian(Vec3(0.7, 0.7, 0.7)));
    list[3] = new Sphere(Vec3(1, 0, -1), 0.5, new Metal(Vec3(0.7), 0));
    list[4] = new Rect(Vec3(-2.6, 2, -4), Vec3(-2.6, 2, 0), Vec3(3.1, 0, -4), new Lambertian(Vec3(1, 0.2, 0.2)));
    list[5] = new Rect(Vec3(-2, 0, -0.5), Vec3(-1, -1, 0), Vec3(-1, 1, -1), new Lambertian(Vec3(1, 1, 0.2)));

    int dielectrics = 1;
    list[6] = new Sphere(Vec3(2, 0, -1), 0.5, new Dielectric(1.025));
    return new HitableList(list, n, n - dielectrics);
}

PointLight** scene_lighting() {
    PointLight** list = new PointLight*[1];
    list[0] = new PointLight(Vec3(2, 1, 2), Vec3(1, 0, 0));
    list[1] = new PointLight(Vec3(-3, 1, 2), Vec3(0, 0, 1));
    list[2] = new PointLight(Vec3(0, 0.5, 2), Vec3(0.0001));

    return list;
}
