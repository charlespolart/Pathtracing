#include "BSDF.h"

Vector3d BSDF::reflection(const Vector3d &I, const Vector3d &N)
{
    return (I - N * N.dotProduct(I) * 2.0);
}

double BSDF::fresnel(const Vector3d &I, const Vector3d &N, double ior)
{
    double kr = 0.0;
    double cosi = std::min(std::max(I.dotProduct(N), -1.0), 1.0);
    double etai = 1.0, etat = ior;
    if (cosi > 0) { std::swap(etai, etat); }
    // Compute sini using Snell's law
    double sint = etai / etat * std::sqrt(std::max(0.0, 1.0 - cosi * cosi));
    // Total internal reflection
    if (sint >= 1.0) {
        kr = 1.0;
    }
    else {
        double cost = std::sqrt(std::max(0.0, 1.0 - sint * sint));
        cosi = std::fabs(cosi);
        double Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost));
        double Rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost));
        kr = (Rs * Rs + Rp * Rp) / 2.0;
    }
    // As a consequence of the conservation of energy, transmittance is given by:
    // kt = 1 - kr;
    return (kr);
}

Vector3d BSDF::transmission(const Vector3d &I, const Vector3d &N, double ior)
{
    double cosi = std::clamp(I.dotProduct(N), -1.0, 1.0);
    double etai = 1.0, etat = ior;
    Vector3d n = N;
    if (cosi < 0.0) { cosi = -cosi; } else { std::swap(etai, etat); n = N * -1.0; }
    double eta = etai / etat;
    double k = 1.0 - eta * eta * (1.0 - cosi * cosi);
    return (k < 0.0 ? BSDF::reflection(I, N) : I * eta + n * (eta * cosi - std::sqrt(k)));
}

double BSDF::uniform_random(double a, double b)
{
    static thread_local std::mt19937 gen(std::hash<std::thread::id>() (std::this_thread::get_id()));
    std::uniform_real_distribution<double> dis(a, b);

    return (dis(gen));
}

Vector3d BSDF::random_direction(const Vector3d &dir, double spread)
{
    // Make an orthogonal basis whose third vector is along `direction'
    Vector3d different = (std::abs(dir.x) < 0.5) ? Vector3d(1.0, 0.0, 0.0) : Vector3d(0.0, 1.0, 0.0);
    Vector3d b1 = dir.crossProduct(different).normalise();
    Vector3d b2 = b1.crossProduct(dir);

    // Pick (x,y,z) randomly around (0,0,1)
    double z = BSDF::uniform_random(std::cos(spread * M_PI), 1.0);
    double r = std::sqrt(1.0 - z*z);
    double theta = BSDF::uniform_random(-M_PI, +M_PI);
    double x = r * std::cos(theta);
    double y = r * std::sin(theta);

    // Construct the vector that has coordinates (x,y,z) in the basis formed by b1, b2, b3
    return (b1*x + b2*y + dir*z);
}

Vector3d BSDF::cook(const Vector3d &dir, const Vector3d &normal, Material *material, Vector3d &radiance)
{
    Vector3d newDir;

    if (material->surface == REFLECTION)
    {
        radiance = material->color;
        return (BSDF::random_direction(BSDF::reflection(dir, normal), material->roughness/2.0));
    }
    else if (material->surface == TRANSMISSION)
    {
        static thread_local std::mt19937 gen(std::hash<std::thread::id>() (std::this_thread::get_id()));
        std::uniform_real_distribution<double> dis(0.0, 1.0);
        double rand = dis(gen);
        double kr = BSDF::fresnel(dir, normal, material->ior);

        radiance = material->color;
        if (rand < kr || kr >= 1.0)
            return (BSDF::random_direction(BSDF::reflection(dir, normal), material->roughness/2.0));
        return (BSDF::random_direction(BSDF::transmission(dir, normal, material->ior), material->roughness/2.0));
    }
    newDir = BSDF::random_direction(normal);
    radiance = material->color*newDir.dotProduct(normal);
    return (newDir);
}
