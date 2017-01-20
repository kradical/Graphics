#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <cmath>


struct rgba8 {
    unsigned char r, g, b, a;
    rgba8() { }
    rgba8(unsigned char rr, unsigned char gg, unsigned char bb, unsigned char aa)
    : r(rr),g(gg),b(bb),a(aa) { }
};
struct vec3 {
    float x, y, z;
    vec3() { }
    vec3(float xx, float yy, float zz)
    : x(xx), y(yy), z(zz) { }
};
struct ray {
    vec3 o, d;
    ray() { }
    ray(vec3 oo, vec3 dd)
    : o(oo), d(dd) { }
};
struct triangle {
    vec3 a, b, c;
    triangle() { }
    triangle(vec3 aa, vec3 bb, vec3 cc)
    : a(aa), b(bb), c(cc) { }
};

rgba8 hdr_to_ldr(vec3 hdr) { return rgba8((unsigned char)(255 * powf(hdr.x, 1.0f / 2.2f)), (unsigned char)(255 * powf(hdr.y, 1.0f / 2.2f)), (unsigned char)(255 * powf(hdr.z, 1.0f / 2.2f)), 255); }
vec3 cross(vec3 a, vec3 b) { return vec3(a.y * b.z - b.y * a.z, a.z * b.x - b.z * a.x, a.x * b.y - b.x * a.y); }
float dot(vec3 a, vec3 b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
float length(vec3 v) { return sqrtf(dot(v, v)); }
vec3 operator+(vec3 a, vec3 b) { return vec3(a.x + b.x, a.y + b.y, a.z + b.z); }
vec3 operator-(vec3 a, vec3 b) { return vec3(a.x - b.x, a.y - b.y, a.z - b.z); }
vec3 operator-(vec3 v) { return vec3(-v.x, -v.y, -v.z); }
vec3 operator*(float u, vec3 v) { return vec3(u * v.x, u * v.y, u * v.z); }
vec3 operator*(vec3 v, float u) { return u * v; }
vec3 operator/(vec3 v, float u) { return vec3(v.x / u, v.y / u, v.z / u); }

bool intersect(ray r, triangle tr, vec3* bary) {
    // Compute normal of triangle (see slide 3 of ray3.pdf.)
    vec3 n;
    n = cross(tr.b - tr.a, tr.b - tr.c);
    
    // Compute distance of ray origin to triangle (see slide 3 of ray3.pdf.)
    float t = dot(n, tr.b - r.o) / dot(n, r.d);

    // Compute point of intersection (see slide 3 of ray3.pdf.)
    vec3 p = r.o + t * r.d;

    // Compute the 3 equations in the green square on the right side of slide 3 of ray3.pdf.
    // If the signs of the three equations differ, then return false.
    float e1 = dot(cross(tr.b - tr.a, p - tr.a), n);
    float e2 = dot(cross(tr.c - tr.b, p - tr.b), n);
    float e3 = dot(cross(tr.a - tr.c, p - tr.c), n);

    float e12 = e1 * e2;
    float e23 = e2 * e3;

    if (e12 * e23 > 0){
        // Compute barycentric coordinates at point p.
        // See slide 12 of ray3.pdf.
        // Hint: area(A,B,C) == length(cross(B - A, C - A)) / 2
        bary->x = length(cross(tr.a - p, tr.b - p)) / length(n);
        bary->y = length(cross(tr.b - p, tr.c - p)) / length(n);
        bary->z = length(cross(tr.c - p, tr.a - p)) / length(n);
        return true;
    }
    
    return false;
}

void raytrace() {
    // allocate image
    int width = 640;
    int height = 480;
    rgba8* pixels = new rgba8[width * height];

    // clear to black
    memset(pixels, 0, width * height * sizeof(*pixels));

    // the triangle to intersect
    triangle tr = triangle(vec3(-1.0f, -1.0f, 0.0f), vec3(1.0f, -1.0f, 0.0f), vec3(1.0f, 1.0f, 0.0f));

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // construct ray for this pixel (orthographic projection)
            ray r;
            r.o = vec3(x / (width / 2.0f) - 1.0f, (height - y - 1) / (height / 2.0f) - 1.0f, 0.0f);
            r.d = vec3(0.0f, 0.0f, 1.0f);

            // test ray intersection with the triangle
            vec3 bary;
            if (intersect(r, tr, &bary)) {
                // if the triangle intersected, output the barycentric coordinate as color.
                pixels[y * width + x] = hdr_to_ldr(bary);
            }
        }
    }

    // write image to file
    stbi_write_png("raytrace.png", width, height, 4, pixels, width * 4);

#ifdef _WIN32
    // Display the image automatically on Windows
    system("raytrace.png");
#else
    // Display the image automatically on MacOS
    system("open raytrace.png");
#endif

    delete[] pixels;
}

void rasterize() {
    // allocate image
    int width = 640;
    int height = 480;
    rgba8* pixels = new rgba8[width * height];
    
    // clear to black
    memset(pixels, 0, width * height * sizeof(*pixels));
    
    // the triangle to intersect
    // note: z = 0 since we assume it's already projected onto the screen...
    triangle tr = triangle(vec3(-1.0f, -1.0f, 0.0f), vec3(1.0f, -1.0f, 0.0f), vec3(1.0f, 1.0f, 0.0f));
    
    // Compute double the area of the triangle.
    vec3 n = cross(tr.b - tr.a, tr.c - tr.a);
    float double_area = length(n);
    n = n / length(n);
    
    // top left of the image (initial evaluation for the barycentric)
    vec3 p = vec3(-1.0f, 1.0f, 0.0f);
    
    // compute barycentric coordinates at p. (x = -1, y = 1, the top left corner of image)
    vec3 bary;
    bary.x = dot(n, cross(tr.b - p, tr.c - p)) / double_area;
    bary.y = dot(n, cross(tr.a - p, tr.b - p)) / double_area;
    bary.z = dot(n, cross(tr.c - p, tr.a - p)) / double_area;
    
    bary = -bary;

    // TODO: Compute screen-space derivatives of barycentric coordinates
    vec3 dbarydx = vec3((tr.b - tr.a).y, (tr.c - tr.b).y, (tr.a - tr.c).y) / double_area;
    vec3 dbarydy = vec3(-(tr.b - tr.a).x, -(tr.c - tr.b).x, -(tr.a - tr.c).x) / double_area;
    
    // scale the coordinate space of the derivatives to fit the image size
    dbarydx = dbarydx / (width / 2.0f);
    dbarydy = dbarydy / (height / 2.0f);
    
    for (int y = 0; y < height; y++)
    {
        vec3 row_bary = bary;
        
        for (int x = 0; x < width; x++)
        {
            // test if all barycentrics are inside the triangle
            if (row_bary.x < 0.0f && row_bary.y < 0.0f && row_bary.z < 0.0f)
            {
                // if the triangle intersected, output the barycentric coordinate as color.
                pixels[y * width + x] = hdr_to_ldr(-row_bary);
            }
            
            row_bary = row_bary + dbarydx;
        }
        
        bary = bary - dbarydy;
    }

    // write image to file
    stbi_write_png("rasterize.png", width, height, 4, pixels, width * 4);

#ifdef _WIN32
    // Display the image automatically on Windows
    system("rasterize.png");
#else
    // Display the image automatically on MacOS
    system("open rasterize.png");
#endif

    delete[] pixels;
}

int main() {
    // comment out one of these
    //raytrace();
    rasterize();
}
