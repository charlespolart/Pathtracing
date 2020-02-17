#ifndef CASTRAY_H
#define CASTRAY_H

#include "Vector.h"
#include "Obj3d.h"
#include "Ray.h"
#include "CollisionTree.h"

struct collisionData_t
{
    double t = 0.0;
    double u = 0.0;
    double v = 0.0;
    Vector3d vn0, vn1, vn2;
    Vector3d position;
    Vector3d normal;
    Material *material;
};

class CastRay
{
public:
    static bool aabb_raycast(const boundingBox_t *bBox, const Ray &ray);
    static bool triangle_raycast(const Ray &ray, const Vector3d &vert0, const Vector3d &vert1, const Vector3d &vert2, double *t, double *u, double *v);
    static void browseTree(const Ray &ray, const treeNode_t *node, collisionData_t &collisionData);
    static Vector3d normalInterpolation(const collisionData_t &collisionData);
    static bool castRay(const Ray &ray, const treeNode_t *treeNode, collisionData_t &collisionData);
};

#endif // CASTRAY_H
