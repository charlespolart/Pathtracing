#ifndef OBJ3D_H
#define OBJ3D_H

#include <vector>
#include <string>
#include "Vector.h"
#include "Material.h"

struct vertices_t
{
    std::vector<Vector3d> v;
    std::vector<Vector3d> vt;
    std::vector<Vector3d> vn;
};

struct face3_t
{
    int indexV[3] = {0, 0, 0};
    int indexVt[3] = {0, 0, 0};
    int indexVn[3] = {0, 0, 0};
};

class Obj3d
{
public:
    Obj3d();
    ~Obj3d();

public:
    std::string name;
    vertices_t *vertices;
    std::vector<face3_t> faces3;
    void *collisionTree;
    Material *material;
};

#endif // OBJ3D_H
