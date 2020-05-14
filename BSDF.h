#ifndef BSDF_H
#define BSDF_H

#include <random>
#include <cstdlib>
#include <thread>
#include "Vector.h"
#include "Material.h"

class BSDF
{
public:
    static Vector3d cook(const Vector3d &dir, const Vector3d &normal, Material *material, Vector3d &radiance);

private:
    static Vector3d reflection(const Vector3d &I, const Vector3d &N);
    static double fresnel(const Vector3d &I, const Vector3d &N, double ior);
    static Vector3d transmission(const Vector3d &I, const Vector3d &N, double ior);
    static double uniform_random(double a, double b);
    static Vector3d random_direction(const Vector3d &dir, double spread = 0.5);
};

#endif // BSDF_H
