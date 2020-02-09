#include "Vector.h"

/* VECTOR3D */
Vector3d::Vector3d() :
    x(0.0), y(0.0), z(0.0)
{
}

Vector3d::Vector3d(double x, double y, double z) :
    x(x), y(y), z(z)
{
}

Vector3d &Vector3d::normalise()
{
    double norm = std::sqrt(this->x*this->x + this->y*this->y + this->z*this->z);

    if (norm == 0.0)
        return (*this);
    this->x /= norm;
    this->y /= norm;
    this->z /= norm;
    return (*this);
}

Vector3d Vector3d::crossProduct(const Vector3d &v) const
{
    Vector3d cross;

    cross.x = this->y*v.z - this->z*v.y;
    cross.y = this->z*v.x - this->x*v.z;
    cross.z = this->x*v.y - this->y*v.x;
    return (cross);
}

double Vector3d::dotProduct(const Vector3d &v) const
{
    return (this->x*v.x + this->y*v.y + this->z*v.z);
}

void Vector3d::rotationX(double angle)
{
  Vector3d mat1;
  Vector3d mat2;
  Vector3d mat3;
  Vector3d tmp;
  double angleTmp;

  if (angle < 0.0 || angle > 0.0)
    {
      angleTmp = (M_PI * angle) / 180.0;
      mat1 = Vector3d(1.0, 0.0, 0.0);
      mat2 = Vector3d(0.0, std::cos(angleTmp), -std::sin(angleTmp));
      mat3 = Vector3d(0.0, std::sin(angleTmp), std::cos(angleTmp));
      tmp = *this;
      this->x = mat1.x * tmp.x + mat1.y * tmp.y + mat1.z * tmp.z;
      this->y = mat2.x * tmp.x + mat2.y * tmp.y + mat2.z * tmp.z;
      this->z = mat3.x * tmp.x + mat3.y * tmp.y + mat3.z * tmp.z;
    }
}

void Vector3d::rotationY(double angle)
{
  Vector3d mat1;
  Vector3d mat2;
  Vector3d mat3;
  Vector3d tmp;
  double angleTmp;

  if (angle < 0.0 || angle > 0.0)
    {
      angleTmp = (M_PI * angle) / 180.0;
      mat1 = Vector3d(std::cos(angleTmp), 0.0, -std::sin(angleTmp));
      mat2 = Vector3d(0.0, 1.0, 0.0);
      mat3 = Vector3d(std::sin(angleTmp), 0.0, std::cos(angleTmp));
      tmp = *this;
      this->x = mat1.x * tmp.x + mat1.y * tmp.y + mat1.z * tmp.z;
      this->y = mat2.x * tmp.x + mat2.y * tmp.y + mat2.z * tmp.z;
      this->z = mat3.x * tmp.x + mat3.y * tmp.y + mat3.z * tmp.z;
    }
}

void Vector3d::rotationZ(double angle)
{
  Vector3d mat1;
  Vector3d mat2;
  Vector3d mat3;
  Vector3d tmp;
  double angleTmp;

  if (angle < 0.0 || angle > 0.0)
    {
      angleTmp = (M_PI * angle) / 180.0;
      mat1 = Vector3d(std::cos(angleTmp), -std::sin(angleTmp), 0.0);
      mat2 = Vector3d(std::sin(angleTmp), std::cos(angleTmp), 0.0);
      mat3 = Vector3d(0.0, 0.0, 1.0);
      tmp = *this;
      this->x = mat1.x * tmp.x + mat1.y * tmp.y + mat1.z * tmp.z;
      this->y = mat2.x * tmp.x + mat2.y * tmp.y + mat2.z * tmp.z;
      this->z = mat3.x * tmp.x + mat3.y * tmp.y + mat3.z * tmp.z;
    }
}

void Vector3d::rotation(const Vector3d &angle)
{
  this->rotationX(angle.x);
  this->rotationY(angle.y);
  this->rotationZ(angle.z);
}

Vector3d Vector3d::operator+(double nb) const
{
    Vector3d res;

    res.x = this->x + nb;
    res.y = this->y + nb;
    res.z = this->z + nb;
    return (res);
}

Vector3d Vector3d::operator+(const Vector3d &v) const
{
    Vector3d res;

    res.x = this->x + v.x;
    res.y = this->y + v.y;
    res.z = this->z + v.z;
    return (res);
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
    Vector3d res;

    res.x = this->x - nb;
    res.y = this->y - nb;
    res.z = this->z - nb;
    return (res);
}

Vector3d Vector3d::operator-(const Vector3d &v) const
{
    Vector3d res;

    res.x = this->x - v.x;
    res.y = this->y - v.y;
    res.z = this->z - v.z;
    return (res);
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
    Vector3d res;

    res.x = this->x * nb;
    res.y = this->y * nb;
    res.z = this->z * nb;
    return (res);
}

Vector3d Vector3d::operator*(const Vector3d &v) const
{
    Vector3d res;

    res.x = this->x * v.x;
    res.y = this->y * v.y;
    res.z = this->z * v.z;
    return (res);
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
    Vector3d res;

    res.x = this->x / nb;
    res.y = this->y / nb;
    res.z = this->z / nb;
    return (res);
}

Vector3d Vector3d::operator/(const Vector3d &v) const
{
    Vector3d res;

    res.x = this->x / v.x;
    res.y = this->y / v.y;
    res.z = this->z / v.z;
    return (res);
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
    if (this->x < nb || this->x > nb || this->y < nb || this->y > nb || this->z < nb || this->z > nb)
        return (false);
    return (true);
}

bool Vector3d::operator!=(double nb)
{
    if (this->x < nb || this->x > nb || this->y < nb || this->y > nb || this->z < nb || this->z > nb)
        return (true);
    return (false);
}
