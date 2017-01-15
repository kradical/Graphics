#ifndef __VEC3__
#define __VEC3__

#include <math.h>
#include <ostream>

class Vec3 {
public:
    float e[3];

    Vec3();
    Vec3(float e_all);
    Vec3(float e0, float e1, float e2);

    inline float x() const;
    inline float y() const;
    inline float z() const;

    inline float r() const;
    inline float g() const;
    inline float b() const;

    inline const Vec3& operator+() const;
    inline Vec3 operator-() const;
    inline float operator[](int i) const;
    inline float& operator[](int i);
    inline const Vec3& operator+=(const Vec3 &v);
    inline const Vec3& operator/=(const float t);

    inline float length() const;
    inline float squared_length() const;
};

inline float Vec3::x() const { return e[0]; }
inline float Vec3::y() const { return e[1]; }
inline float Vec3::z() const { return e[2]; }

inline float Vec3::r() const { return e[0]; }
inline float Vec3::g() const { return e[1]; }
inline float Vec3::b() const { return e[2]; }

inline const Vec3& Vec3::operator+() const { return *this; }
inline Vec3 Vec3::operator-() const { return Vec3(-e[0], -e[1], -e[2]); }
inline float Vec3::operator[](int i) const { return e[i]; }
inline float& Vec3::operator[](int i) { return e[i]; }
inline const Vec3& Vec3::operator+=(const Vec3 &v) {
    e[0] += v[0];
    e[1] += v[1];
    e[2] += v[2];
}
inline const Vec3& Vec3::operator/=(const float t) {
    e[0] /= t;
    e[1] /= t;
    e[2] /= t;
}

inline float Vec3::length() const { return sqrt(squared_length()); }
inline float Vec3::squared_length() const { return e[0] * e[0] + e[1] * e[1] + e[2] * e[2]; }

inline Vec3 operator+(const Vec3& v1, const Vec3& v2) {
    return Vec3(v1[0] + v2[0], v1[1] + v2[1], v1[2] + v2[2]);
}

inline Vec3 operator-(const Vec3 &v1, const Vec3 &v2) {
    return Vec3(v1[0] - v2[0], v1[1] - v2[1], v1[2] - v2[2]);
}

inline Vec3 operator*(const Vec3 &v1, const Vec3 &v2) {
    return Vec3(v1[0] * v2[0], v1[1] * v2[1], v1[2] * v2[2]);
}

inline Vec3 operator*(const float t, const Vec3& v) {
    return Vec3(t * v[0], t * v[1], t * v[2]);
}

inline Vec3 operator*(const Vec3& v, const float t) {
    return Vec3(t * v[0], t * v[1], t * v[2]);
}

inline Vec3 operator/(const Vec3& v, const float t) {
    return Vec3(v[0] / t, v[1] / t, v[2] / t);
}

// debugging print
inline std::ostream& operator<<(std::ostream &os, const Vec3& v) { 
    return os << "[ " << v[0] << ", " << v[1] << ", " << v[2] << " ]";
}

inline float dot(const Vec3 &v1, const Vec3 &v2) {
    return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

inline Vec3 cross(const Vec3& a, const Vec3& b) {
    return Vec3(a[1] * b[2] - a[2] * b[1],
        a[2] * b[0] - a[0] * b[2],
        a[0] * b[1] - a[1] * b[0]);
}

inline Vec3 unit_vector(Vec3 v) {
    return v / v.length();
}

#endif
