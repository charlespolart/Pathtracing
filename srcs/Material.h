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
};

struct texture_t
{
    int x = 0, y = 0;
    uint8_t *pixels = nullptr;
};

class Material
{
public:
    Material();
    ~Material();

public:
    std::string _name;
    surface_e _surface;
    Vector3d _color;
    double _emission;
    double _roughness;
    double _ior;
    texture_t _texture;
};

Q_DECLARE_METATYPE(Material *)

#endif // MATERIAL_H
