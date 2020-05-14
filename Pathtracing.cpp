#include "Pathtracing.h"

Vector3d Pathtracing::render(const Ray &ray, Scene *scene, int depth)
{
    Vector3d hitPointColor, radiance;
    Vector3d dir;
    collisionData_t collisionData;

    if (CastRay::castRay(ray, scene->mesh.collisionTree, collisionData) && depth <= scene->maxDepth)
    {
        if (collisionData.material->surface == EMISSION)
            return (collisionData.material->color * collisionData.material->emission);
        dir = BSDF::cook(ray.direction, collisionData.normal, collisionData.material, radiance);
        hitPointColor = Pathtracing::render(Ray(collisionData.position, dir), scene, depth+1);
    }
    return (hitPointColor*radiance);
}
