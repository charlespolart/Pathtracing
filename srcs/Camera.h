#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include <algorithm>
#include "Vector.h"
#include "Ray.h"

class Camera
{
public:
    Camera();

    void setWidth(int width);
    void setHeight(int height);
    void setFOV(int FOV);

    Ray initRay(double x, double y) const;

public:
    int _width;
    int _height;
    Vector3d _position;
    Vector3d _rotation;
    double _FOV;
    double _aspectRatio;

private:
    double _scale;
    bool _inv;
};

#endif // CAMERA_H
