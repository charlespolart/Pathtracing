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

Vector3d cosineSampleHemisphere()
{
    double u1 = Rand::uniform_random(0.0, 1.0);
    double u2 = Rand::uniform_random(0.0, 1.0);
    double r = std::sqrt(u1);
    double theta = 2.0 * M_PI * u2;

    double x = r * std::cos(theta);
    double y = r * std::sin(theta);

    return (Vector3d(x, y, std::sqrt(std::max(0.0, 1.0 - u1))));
}

Vector3d uniformSampleHemisphere()
{
    double r1 = Rand::uniform_random(0.0, 1.0);
    double r2 = Rand::uniform_random(0.0, 1.0);
    double sinTheta = std::sqrt(1.0 - r1 * r1);
    double phi = 2.0 * M_PI * r2;
    double x = sinTheta * cosf(phi);
    double z = sinTheta * sinf(phi);
    return (Vector3d(x, r1, z));
    /*double u1 = Rand::uniform_random(0.0, 1.0);
    double u2 = Rand::uniform_random(0.0, 1.0);
    double r = std::sqrt(1.0 - u1 * u1);
    double phi = 2.0 * M_PI * u2;

    return (Vector3d(std::cos(phi) * r, u1, std::sin(phi) * r));*/
}

void createCoordinateSystem(const Vector3d &N, Vector3d &Nt, Vector3d &Nb)
{
    if (std::fabs(N.x) > std::fabs(N.y))
        Nt = Vector3d(N.z, 0.0, -N.x) / std::sqrt(N.x * N.x + N.z * N.z);
    else
        Nt = Vector3d(0.0, -N.z, N.y) / std::sqrt(N.y * N.y + N.z * N.z);
    Nb = N.crossProduct(Nt);
}

Vector3d sampleHemisphere(const Vector3d &hitNormal)
{
    Vector3d Nt, Nb;
    createCoordinateSystem(hitNormal, Nt, Nb);
    Vector3d sample = uniformSampleHemisphere();
    Vector3d sampleWorld(sample.x * Nb.x + sample.y * hitNormal.x + sample.z * Nt.x,
                         sample.x * Nb.y + sample.y * hitNormal.y + sample.z * Nt.y,
                         sample.x * Nb.z + sample.y * hitNormal.z + sample.z * Nt.z);
    return (sampleWorld);
}

Vector3d BSDF::random_in_hemisphere(const Vector3d &direction, double spread)
{
    // Make an orthogonal basis whose third vector is along `direction'
    Vector3d different = (std::abs(direction.x) < 0.5) ? Vector3d(1.0, 0.0, 0.0) : Vector3d(0.0, 1.0, 0.0);
    Vector3d b1 = direction.crossProduct(different).normalise();
    Vector3d b2 = b1.crossProduct(direction);

    // Pick (x,y,z) randomly around (0,0,1)
    double z = Rand::uniform_random(std::cos(spread * M_PI), 1.0);
    double r = std::sqrt(1.0 - z*z);
    double theta = Rand::uniform_random(-M_PI, +M_PI);
    double x = r * std::cos(theta);
    double y = r * std::sin(theta);

    // Construct the vector that has coordinates (x,y,z) in the basis formed by b1, b2, b3
    return (b1*x + b2*y + direction*z);
}

sample_t BSDF::cook(const Vector3d &direction, const Vector3d &normal, Material *material, const Vector3d &hitPointColor)
{
    if (material->_surface == REFLECTION)
    {
        Vector3d reflected = BSDF::random_in_hemisphere(BSDF::reflection(direction, normal), material->_roughness/2.0);
        Vector3d radiance = hitPointColor;
        return (sample_t { reflected, radiance });
    }
    else if (material->_surface == TRANSMISSION)
    {
        //bool exiting = direction.dotProduct(normal) >= 0.0;
        double fresnel = BSDF::fresnel(direction, normal, material->_ior);
        Vector3d refracted = Rand::uniform_random(0.0, 1.0) < fresnel ? BSDF::reflection(direction, normal) :
                                                                        BSDF::transmission(direction, normal, material->_ior);
        Vector3d radiance = hitPointColor;

        return (sample_t { refracted, radiance });
    }
    /*else if (material->surface == TRANSMISSION)
    {
        double kr = BSDF::fresnel(direction, normal, material->ior);
        double rand = BSDF::uniform_random(0.0, 1.0);

        radiance = hitPointColor;
        if (rand < kr || kr >= 1.0)
            return (BSDF::random_direction(BSDF::reflection(direction, normal), material->roughness/2.0));
        return (BSDF::random_direction(BSDF::transmission(direction, normal, material->ior), material->roughness/2.0));
    }*/
    /* DIFFUSE */
    //Vector3d diffuse = BSDF::random_in_hemisphere(normal);
    Vector3d diffuse = sampleHemisphere(normal);
    double cos = std::max(0.0, diffuse.dotProduct(normal));
    Vector3d radiance = hitPointColor * cos;
    //std::cout << diffuse.x << " " << diffuse.y << " " << diffuse.z << std::endl;
    return (sample_t { diffuse, radiance });
}
