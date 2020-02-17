#include "Obj3d.h"

Obj3d::Obj3d() :
    material(new Material())
{
}

Obj3d::~Obj3d()
{
    delete this->material;
}
