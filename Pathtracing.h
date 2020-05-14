#ifndef PATHTRACING_H
#define PATHTRACING_H

#include "Scene.h"
#include "CastRay.h"
#include "BSDF.h"

class Pathtracing
{
public:
    static Vector3d render(const Ray &ray, Scene *scene, int depth = 0);
};

#endif // PATHTRACING_H
