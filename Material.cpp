#include "Material.h"

Material::Material() :
    name(""),
    surface(DIFFUSE),
    color(1.0, 1.0, 1.0),
    emission(0.0),
    roughness(0.0),
    ior(0.0)
{
}
