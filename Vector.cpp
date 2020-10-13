#include "Vector.h"

/* VECTOR3D */
Vector3d::Vector3d() :
    x(0.0), y(0.0), z(0.0)
{
}

Vector3d::Vector3d(double c) :
    x(c), y(c), z(c)
{
}

Vector3d::Vector3d(double x, double y, double z) :
    x(x), y(y), z(z)
{
}

double Vector3d::max() const
{
    return (std::max(this->x, std::max(this->y, this->z)));
}

double Vector3d::min() const
{
    return (std::min(this->x, std::min(this->y, this->z)));
}

double Vector3d::average() const
{
    return ((this->x + this->y + this->z) / 3.0);
}

Vector3d Vector3d::progressiveAverage(const Vector3d &v, int samples) const
{
    return (*this + (v - *this) / samples);
}

Vector3d Vector3d::normalise() const
{
    double norm = std::sqrt(this->x*this->x + this->y*this->y + this->z*this->z);

    return (norm == 0.0 ? *this : *this/norm);
}

Vector3d Vector3d::crossProduct(const Vector3d &v) const
{
    return (Vector3d(this->y*v.z - this->z*v.y,
                     this->z*v.x - this->x*v.z,
                     this->x*v.y - this->y*v.x));
}

double Vector3d::dotProduct(const Vector3d &v) const
{
    return (this->x*v.x + this->y*v.y + this->z*v.z);
}

Vector3d Vector3d::lerp(const Vector3d &v, double nb)
{
    double m = 1.0 - nb;

    return (Vector3d(this->x * m + v.x * nb, this->y * m + v.y * nb, this->z * m + v.z * nb));
}

Vector3d Vector3d::rotationX(double angle) const
{
    if (angle == 0.0) return (*this);
    angle = (M_PI * -angle) / 180.0;
    return (Vector3d(this->dotProduct(Vector3d(1.0, 0.0, 0.0)),
                     this->dotProduct(Vector3d(0.0, std::cos(angle), -std::sin(angle))),
                     this->dotProduct(Vector3d(0.0, std::sin(angle), std::cos(angle)))));
}

Vector3d Vector3d::rotationY(double angle) const
{
    if (angle == 0.0) return (*this);
    angle = (M_PI * angle) / 180.0;
    return (Vector3d(this->dotProduct(Vector3d(std::cos(angle), 0.0, -std::sin(angle))),
                     this->dotProduct(Vector3d(0.0, 1.0, 0.0)),
                     this->dotProduct(Vector3d(std::sin(angle), 0.0, std::cos(angle)))));
}

Vector3d Vector3d::rotationZ(double angle) const
{
    if (angle == 0.0) return (*this);
    angle = (M_PI * angle) / 180.0;
    return (Vector3d(this->dotProduct(Vector3d(std::cos(angle), -std::sin(angle), 0.0)),
                     this->dotProduct(Vector3d(std::sin(angle), std::cos(angle), 0.0)),
                     this->dotProduct(Vector3d(0.0, 0.0, 1.0))));
}

Vector3d Vector3d::rotation(const Vector3d &angle) const
{
    return (this->rotationX(angle.x).rotationY(angle.y).rotationZ(angle.z));
}

Vector3d Vector3d::operator+(double nb) const
{
    return (Vector3d(this->x + nb,
                     this->y + nb,
                     this->z + nb));
}

Vector3d Vector3d::operator+(const Vector3d &v) const
{
    return (Vector3d(this->x + v.x,
                     this->y + v.y,
                     this->z + v.z));
}

Vector3d &Vector3d::operator+=(double nb)
{
    this->x += nb;
    this->y += nb;
    this->z += nb;
    return (*this);
}

Vector3d &Vector3d::operator+=(const Vector3d &v)
{
    this->x += v.x;
    this->y += v.y;
    this->z += v.z;
    return (*this);
}

Vector3d Vector3d::operator-(double nb) const
{
    return (Vector3d(this->x - nb,
                     this->y - nb,
                     this->z - nb));
}

Vector3d Vector3d::operator-(const Vector3d &v) const
{
    return (Vector3d(this->x - v.x,
                     this->y - v.y,
                     this->z - v.z));
}

Vector3d &Vector3d::operator-=(double nb)
{
    this->x -= nb;
    this->y -= nb;
    this->z -= nb;
    return (*this);
}

Vector3d &Vector3d::operator-=(const Vector3d &v)
{
    this->x -= v.x;
    this->y -= v.y;
    this->z -= v.z;
    return (*this);
}

Vector3d Vector3d::operator*(double nb) const
{
    return (Vector3d(this->x * nb,
                     this->y * nb,
                     this->z * nb));
}

Vector3d Vector3d::operator*(const Vector3d &v) const
{
    return (Vector3d(this->x * v.x,
                     this->y * v.y,
                     this->z * v.z));
}

Vector3d &Vector3d::operator*=(double nb)
{
    this->x *= nb;
    this->y *= nb;
    this->z *= nb;
    return (*this);
}

Vector3d &Vector3d::operator*=(const Vector3d &v)
{
    this->x *= v.x;
    this->y *= v.y;
    this->z *= v.z;
    return (*this);
}

Vector3d Vector3d::operator/(double nb) const
{
    return (Vector3d(this->x / nb,
                     this->y / nb,
                     this->z / nb));
}

Vector3d Vector3d::operator/(const Vector3d &v) const
{
    return (Vector3d(this->x / v.x,
                     this->y / v.y,
                     this->z / v.z));
}

Vector3d &Vector3d::operator/=(double nb)
{
    this->x /= nb;
    this->y /= nb;
    this->z /= nb;
    return (*this);
}

Vector3d &Vector3d::operator/=(const Vector3d &v)
{
    this->x /= v.x;
    this->y /= v.y;
    this->z /= v.z;
    return (*this);
}

bool Vector3d::operator==(double nb)
{
    if (std::abs(this->x - nb) <= __DBL_EPSILON__ && std::abs(this->y - nb) <= __DBL_EPSILON__ && std::abs(this->z - nb) <= __DBL_EPSILON__)
        return (true);
    return (false);
}

bool Vector3d::operator!=(double nb)
{
    if (std::abs(this->x - nb) <= __DBL_EPSILON__ && std::abs(this->y - nb) <= __DBL_EPSILON__ && std::abs(this->z - nb) <= __DBL_EPSILON__)
        return (false);
    return (true);
}

template<typename T>
Vector3d operator+(T nb, const Vector3d &v)
{
    return (v + nb);
}

template<typename T>
Vector3d operator-(T nb, const Vector3d &v)
{
    return (v - nb);
}

template<typename T>
Vector3d operator*(T nb, const Vector3d &v)
{
    return (v * nb);
}
