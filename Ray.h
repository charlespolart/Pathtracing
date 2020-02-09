#ifndef RAY_H
#define RAY_H

#include <limits>
#include "Vector.h"

class Ray
{
public:
    Ray(const Vector3d &origin, const Vector3d &direction) :
        origin(origin),
        direction(direction)
    {
        const double EPSILON = 0.0000001;
        if (this->direction.x == 0.0) this->direction.x = EPSILON;
        if (this->direction.y == 0.0) this->direction.y = EPSILON;
        if (this->direction.z == 0.0) this->direction.z = EPSILON;
        this->direction.normalise();
        this->invDirection = Vector3d(1.0/this->direction.x, 1.0/this->direction.y, 1.0/this->direction.z);
        sign[0] = (this->invDirection.x < 0.0);
        sign[1] = (this->invDirection.y < 0.0);
        sign[2] = (this->invDirection.z < 0.0);
    }

public:
    Vector3d origin;
    Vector3d direction;
    Vector3d invDirection;
    int sign[3];
};

#endif //!RAY_H
