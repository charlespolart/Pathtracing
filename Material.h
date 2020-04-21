#ifndef MATERIAL_H
#define MATERIAL_H

#include <string>
#include <vector>
#include <QMetaType>
#include "Vector.h"

class Material
{
public:
    Material(const std::string &name = "", const Vector3d &color = Vector3d(1.0, 1.0, 1.0), double emission = 0.0);

public:
    std::string name;
    Vector3d color;
    double emission;
};

Q_DECLARE_METATYPE(Material *)

#endif // MATERIAL_H
