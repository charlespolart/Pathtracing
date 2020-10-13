#ifndef RAY_H
#define RAY_H

#include <limits>
#include "Vector.h"

class Ray
{
public:
    Ray(const Vector3d &origin, const Vector3d &direction) :
        _origin(origin),
        _direction(direction)
    {
        const double EPSILON = 0.0000001;
        if (this->_direction.x == 0.0) this->_direction.x = EPSILON;
        if (this->_direction.y == 0.0) this->_direction.y = EPSILON;
        if (this->_direction.z == 0.0) this->_direction.z = EPSILON;
        this->_direction.normalise();
        this->_invDirection = Vector3d(1.0/this->_direction.x, 1.0/this->_direction.y, 1.0/this->_direction.z);
        _sign[0] = (this->_invDirection.x < 0.0);
        _sign[1] = (this->_invDirection.y < 0.0);
        _sign[2] = (this->_invDirection.z < 0.0);
    }

public:
    Vector3d _origin;
    Vector3d _direction;
    Vector3d _invDirection;
    int _sign[3];
};

#endif //!RAY_H
