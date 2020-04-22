#include "Pathtracing.h"

Vector3d Pathtracing::reflection(const Vector3d &I, const Vector3d &N)
{
    return (I - N * N.dotProduct(I) * 2.0);
}

double Pathtracing::uniform_random(double a, double b)
{
    return (a + (static_cast<double>(std::rand())/RAND_MAX) * (b - a));
}

Vector3d Pathtracing::random_direction(const Vector3d &dir, double spread)
{
    // Make an orthogonal basis whose third vector is along `direction'
    Vector3d different = (std::abs(dir.x) < 0.5) ? Vector3d(1.0, 0.0, 0.0) : Vector3d(0.0, 1.0, 0.0);
    Vector3d b1 = dir.crossProduct(different).normalise();
    Vector3d b2 = b1.crossProduct(dir);

    // Pick (x,y,z) randomly around (0,0,1)
    double z = Pathtracing::uniform_random(std::cos(spread * M_PI), 1);
    double r = std::sqrt(1.0 - z*z);
    double theta = Pathtracing::uniform_random(-M_PI, +M_PI);
    double x = r * std::cos(theta);
    double y = r * std::sin(theta);

    // Construct the vector that has coordinates (x,y,z) in the basis formed by b1, b2, b3
    return (b1*x + b2*y + dir*z);
}

Vector3d Pathtracing::render(const Ray &ray, Scene *scene, int depth)
{
    Vector3d hitPointColor, radiance;
    Vector3d randDir;
    collisionData_t collisionData;

    if (CastRay::castRay(ray, scene->mesh.collisionTree, collisionData) && depth <= scene->maxDepth)
    {
        if (collisionData.material->emission > 0.0)
            return (collisionData.material->color * collisionData.material->emission);
        randDir = Pathtracing::random_direction(collisionData.normal);
        radiance = collisionData.material->color*randDir.dotProduct(collisionData.normal);
        hitPointColor = Pathtracing::render(Ray(collisionData.position, randDir), scene, depth+1);
    }
    return (hitPointColor*radiance);
}
