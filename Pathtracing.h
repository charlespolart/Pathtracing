#ifndef PATHTRACING_H
#define PATHTRACING_H

#include "Scene.h"
#include "CastRay.h"

class Pathtracing
{
public:
    static Vector3d render(const Ray &ray, Scene *scene, int depth = 0);

private:
    static Vector3d reflection(const Vector3d &I, const Vector3d &N);
    static double uniform_random(double a, double b);
    static Vector3d random_direction(const Vector3d &dir, double spread = 0.5);
};

#endif // PATHTRACING_H
