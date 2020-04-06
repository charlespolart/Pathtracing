#ifndef MATERIAL_H
#define MATERIAL_H

#include <string>
#include <vector>
#include <QMetaType>
#include "Vector.h"

class Material
{
public:
    Material();

public:
    std::string name;
    Vector3d color;
    double emission;
};

Q_DECLARE_METATYPE(Material *)

#endif // MATERIAL_H
