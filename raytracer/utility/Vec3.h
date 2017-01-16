#ifndef __VEC3__
#define __VEC3__

#include <math.h>
#include <ostream>

class Vec3 {
public:
    float x, y, z;

    Vec3();
    Vec3(float val);
    Vec3(float _x, float _y, float _z);

    inline Vec3 operator-() const;
    inline const Vec3& operator+=(const Vec3 &v);
    inline const Vec3& operator/=(const float t);

    inline float length() const;
    inline float squared_length() const;
};

// add a vector component-wise to this.
inline const Vec3& Vec3::operator+=(const Vec3 &v) {
    x += v.x;
    y += v.y;
    z += v.z;
}
// divide each vector component by a float.
inline const Vec3& Vec3::operator/=(const float t) {
    x /= t;
    y /= t;
    z /= t;
}
// return the negation of this vector.
inline Vec3 Vec3::operator-() const { return Vec3(-x, -y, -z); }

// return vector length.
inline float Vec3::length() const { return sqrt(squared_length()); }
// return the square of the length.
inline float Vec3::squared_length() const { return x * x + y * y + z * z; }

// add two vectors component-wise.
inline Vec3 operator+(const Vec3& v1, const Vec3& v2) {
    return Vec3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}
// return the subtractraction of v2 from v1 componentwise.
inline Vec3 operator-(const Vec3 &v1, const Vec3 &v2) {
    return Vec3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}
// multiply two vectors component-wise.
inline Vec3 operator*(const Vec3 &v1, const Vec3 &v2) {
    return Vec3(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}
// multiple a vectors components by a float.
inline Vec3 operator*(const float t, const Vec3& v) {
    return Vec3(t * v.x, t * v.y, t * v.z);
}
// multiple a vectors components by a float.
inline Vec3 operator*(const Vec3& v, const float t) {
    return Vec3(t * v.x, t * v.y, t * v.z);
}
// divide a vectors components by a float.
inline Vec3 operator/(const Vec3& v, const float t) {
    return Vec3(v.x / t, v.y / t, v.z / t);
}
// dot product of two vectors.
inline float dot(const Vec3 &v1, const Vec3 &v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}
// cross product of two vectors.
inline Vec3 cross(const Vec3& a, const Vec3& b) {
    return Vec3(a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x);
}
// return the unit vector of a vector.
inline Vec3 unit_vector(Vec3 v) {
    return v / v.length();
}

// debugging print
inline std::ostream& operator<<(std::ostream &os, const Vec3& v) { 
    return os << "[ " << v.x << ", " << v.y << ", " << v.z << " ]";
}

#endif
