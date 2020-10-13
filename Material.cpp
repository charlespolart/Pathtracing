#include "Material.h"

Material::Material() :
    _name(""),
    _surface(DIFFUSE),
    _color(1.0, 1.0, 1.0),
    _emission(0.0),
    _roughness(0.0),
    _ior(0.0)
{
}

Material::~Material()
{
    if (this->_texture.pixels)
        delete [] this->_texture.pixels;
}
