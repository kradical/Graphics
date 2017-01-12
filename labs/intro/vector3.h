struct Vector3 {
    float x, y, z;

    Vector3& operator+=(const Vector3& v2) {
        x += v2.x;
        y += v2.y;
        z += v2.z;
    }

    Vector3 operator+(const Vector3& v2) {
        Vector3 newVec;
        newVec.x = x + v2.x;
        newVec.y = y + v2.y;
        newVec.z = z + v2.z;
        return newVec;
    }
};