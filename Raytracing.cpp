#include "Raytracing.h"

Vector3d Raytracing::lightning(const Ray &ray, collisionData_t &collisionData, const Vector2i &pix)
{
    Vector3d color;
    double cosA = 0.0;
    Ray lightRay(collisionData.position, (ray.origin - collisionData.position));

    if (ray.direction.dotProduct(collisionData.normal) >= 0.0)
        collisionData.normal *= -1.0;
    if ((cosA = lightRay.direction.dotProduct(collisionData.normal)) >= 0.0)
    {
        color = collisionData.material->color*cosA;
    }
    return (color);
}

Vector3d Raytracing::render(const Ray &ray, Scene *scene, const Vector2i &pix)
{
    Vector3d color;
    collisionData_t collisionData;

    if (!CastRay::castRay(ray, scene->mesh.collisionTree, collisionData))
        return (color);
    color = Raytracing::lightning(ray, collisionData, pix);
    return (color);
}
