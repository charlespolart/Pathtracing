#ifndef BSDF_H
#define BSDF_H

#include <iostream>
#include <cstdlib>
#include "Vector.h"
#include "Material.h"
#include "Rand.h"

struct sample_t
{
    Vector3d direction;
    Vector3d radiance;
};

class BSDF
{
public:
    static sample_t cook(const Vector3d &dir, const Vector3d &normal, Material *material, const Vector3d &hitPointColor);

private:
    static Vector3d reflection(const Vector3d &I, const Vector3d &N);
    static double fresnel(const Vector3d &I, const Vector3d &N, double ior);
    static Vector3d transmission(const Vector3d &I, const Vector3d &N, double ior);
    static Vector3d random_in_hemisphere(const Vector3d &dir, double spread = 0.5);
};

#endif // BSDF_H
