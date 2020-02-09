#ifndef VECTOR_H
#define VECTOR_H

//#define M_PI 3.14159265358979323846
#define _USE_MATH_DEFINES

#include <cmath>

class Vector3d
{
public:
    Vector3d();
    Vector3d(double x, double y, double z);

public:
    Vector3d &normalise();
    Vector3d crossProduct(const Vector3d &) const;
    double dotProduct(const Vector3d &) const;
    void rotation(const Vector3d &angle);
    void rotationX(double angle);
    void rotationY(double angle);
    void rotationZ(double angle);

public:
    Vector3d operator+(double nb) const;
    Vector3d operator+(const Vector3d &v) const;
    Vector3d &operator+=(double nb);
    Vector3d &operator+=(const Vector3d &v);
    Vector3d operator-(double nb) const;
    Vector3d operator-(const Vector3d &v) const;
    Vector3d &operator-=(double nb);
    Vector3d &operator-=(const Vector3d &v);
    Vector3d operator*(double nb) const;
    Vector3d operator*(const Vector3d &v) const;
    Vector3d &operator*=(double nb);
    Vector3d &operator*=(const Vector3d &v);
    Vector3d operator/(double nb) const;
    Vector3d operator/(const Vector3d &v) const;
    Vector3d &operator/=(double nb);
    Vector3d &operator/=(const Vector3d &v);
    bool operator==(double nb);
    bool operator!=(double nb);

public:
    double x, y, z;
};

class Vector2i
{
public:
    Vector2i() :
        x(0), y(0) {}
    Vector2i(int x, int y) :
        x(x), y(y) {}

public:
    int x, y;
};

#endif // VECTOR_H
