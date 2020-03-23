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

    Ray initRay(int x, int y) const;

public:
    int width;
    int height;
    Vector3d position;
    Vector3d rotation;
    double FOV;

private:
    double scale;
    double aspectRatio;
    bool inv;
};

#endif // CAMERA_H
