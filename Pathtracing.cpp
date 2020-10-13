#include "Pathtracing.h"

Vector3d Pathtracing::render(const Ray &constRay, Scene *scene)
{
    Vector3d throughput(1.0);
    Vector3d radiance(0.0);
    Ray ray = constRay;

    for (int bounces = 0; bounces < scene->_maxDepth; ++bounces)
    {
        collisionData_t collisionData;
        if (!CastRay::castRay(ray, scene->_mesh.collisionTree, collisionData))
        {
            radiance += throughput * Vector3d(0.0);
            break;
        }
        if (collisionData.material->_emission)
            radiance += collisionData.hitPointColor * collisionData.material->_emission * throughput;

        /* Russian roulette */
        /*if (bounces > 4)
        {
            double q = std::max(0.05, throughput.max());
            if (Rand::uniform_random(0.0, 1.0) > q)
                break;
            throughput /= q;
        }*/

        sample_t sample = BSDF::cook(ray._direction, collisionData.normal, collisionData.material, collisionData.hitPointColor);
        throughput *= sample.radiance;

        ray = Ray(collisionData.position, sample.direction);
    }
    return (radiance);
}
