#include "Material.h"

Material::Material(const std::string &name, const Vector3d &color, double emission)
{
    this->name = name;
    this->color = color;
    this->emission = emission;
}
