#ifndef PATHTRACING_H
#define PATHTRACING_H

#include "Scene.h"
#include "CastRay.h"

class Pathtracing
{
public:
    static Vector3d lightning(const Ray &ray, collisionData_t &collisionData, const Vector2i &pix);
    static Vector3d render(const Ray &ray, Scene *scene, const Vector2i &pix);
};

#endif // PATHTRACING_H
