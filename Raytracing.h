#ifndef RAYTRACING_H
#define RAYTRACING_H

#include "Scene.h"
#include "CastRay.h"

class Raytracing
{
public:
    static Vector3d lightning(const Ray &ray, collisionData_t &collisionData, const Vector2i &pix);
    static Vector3d render(const Ray &ray, Scene *scene, const Vector2i &pix);
};

#endif // RAYTRACING_H
