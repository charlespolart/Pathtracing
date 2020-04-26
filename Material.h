#ifndef MATERIAL_H
#define MATERIAL_H

#include <string>
#include <vector>
#include <QMetaType>
#include "Vector.h"

enum surface_e
{
    DIFFUSE,
    REFLECTION,
    TRANSMISSION,
    EMISSION
};

class Material
{
public:
    Material();

public:
    std::string name;
    surface_e surface;
    Vector3d color;
    double emission;
    double roughness;
    double ior;
};

Q_DECLARE_METATYPE(Material *)

#endif // MATERIAL_H
