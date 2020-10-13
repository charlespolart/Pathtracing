#ifndef VECTOR_H
#define VECTOR_H

#define _USE_MATH_DEFINES

#include <cmath>

class Vector3d
{
public:
    Vector3d();
    Vector3d(double c);
    Vector3d(double x, double y, double z);

public:
    Vector3d progressiveAverage(const Vector3d &v, int samples) const;
    double max() const;
    double min() const;
    double average() const;
    Vector3d normalise() const;
    Vector3d crossProduct(const Vector3d &) const;
    double dotProduct(const Vector3d &) const;
    Vector3d lerp(const Vector3d &v, double nb);
    Vector3d rotationX(double angle) const;
    Vector3d rotationY(double angle) const;
    Vector3d rotationZ(double angle) const;
    Vector3d rotation(const Vector3d &angle) const;

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

template<typename T>
Vector3d operator+(T, const Vector3d &v);
template<typename T>
Vector3d operator-(T, const Vector3d &v);
template<typename T>
Vector3d operator*(T, const Vector3d &v);

class Vector2d
{
public:
    Vector2d() :
        x(0), y(0) {}
    Vector2d(int x, int y) :
        x(x), y(y) {}

public:
    double x, y;
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
