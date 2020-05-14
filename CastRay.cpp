#include "CastRay.h"

bool CastRay::aabb_raycast(const boundingBox_t *bBox, const Ray &ray)
{
    double tmin, tmax, tymin, tymax, tzmin, tzmax;

    tmin = (bBox->bounds[ray.sign[0]].x - ray.origin.x) * ray.invDirection.x;
    tmax = (bBox->bounds[1-ray.sign[0]].x - ray.origin.x) * ray.invDirection.x;
    tymin = (bBox->bounds[ray.sign[1]].y - ray.origin.y) * ray.invDirection.y;
    tymax = (bBox->bounds[1-ray.sign[1]].y - ray.origin.y) * ray.invDirection.y;
    if ((tmin > tymax) || (tymin > tmax))
        return (false);
    if (tymin > tmin)
        tmin = tymin;
    if (tymax < tmax)
        tmax = tymax;
    tzmin = (bBox->bounds[ray.sign[2]].z - ray.origin.z) * ray.invDirection.z;
    tzmax = (bBox->bounds[1-ray.sign[2]].z - ray.origin.z) * ray.invDirection.z;
    if ((tmin > tzmax) || (tzmin > tmax))
        return (false);
    if (tzmin > tmin)
        tmin = tzmin;
    if (tzmax < tmax)
        tmax = tzmax;
    return (true);
    //return ((tmin < t1) && (tmax > t0));
}

bool CastRay::triangle_raycast(const Ray &ray, const Vector3d &vert0, const Vector3d &vert1, const Vector3d &vert2, double *t, double *u, double *v)
{
    const double EPSILON = 0.000000001;
    Vector3d edge1, edge2, tvec, pvec, qvec;
    double det, inv_det;

    // find vectors for two edges sharing vert0
    edge1 = vert1 - vert0;
    edge2 = vert2 - vert0;

    // begin calculating determinant - also used to calculate U parameter
    pvec = ray.direction.crossProduct(edge2);

    // if determinant is near zero, ray lies in plane of triangle
    det = edge1.dotProduct(pvec);

    if (det > -EPSILON && det < EPSILON)
        return (0);

    inv_det = 1.0 / det;

    // calculate distance from vert0 to ray origin
    tvec = ray.origin - vert0;

    // calculate U parameter and test bounds
    *u = tvec.dotProduct(pvec) * inv_det;
    if (*u < 0.0 || *u > 1.0)
        return (false);

    // prepare to test V parameter
    qvec = tvec.crossProduct(edge1);

    // calculate V parameter and test bounds
    *v = ray.direction.dotProduct(qvec) * inv_det;
    if (*v < 0.0 || *u + *v > 1.0)
        return (false);

    // calculate t, ray intersects triangle
    *t = edge2.dotProduct(qvec) * inv_det;

    if (*t < EPSILON)
        return (false);

    return (true);
}

void CastRay::browseTree(const Ray &ray, const treeNode_t *node, collisionData_t &collisionData)
{
    double t = 0.0, u = 0.0, v = 0.0;

    if (!node || !CastRay::aabb_raycast(node->bBox, ray))
        return;
    CastRay::browseTree(ray, node->nxt1, collisionData);
    CastRay::browseTree(ray, node->nxt2, collisionData);

    if (node->obj3d
            && CastRay::triangle_raycast(ray,
                                         node->obj3d->vertices->v[node->obj3d->faces3[node->faceIndex].indexV[0] - 1],
                                         node->obj3d->vertices->v[node->obj3d->faces3[node->faceIndex].indexV[1] - 1],
                                         node->obj3d->vertices->v[node->obj3d->faces3[node->faceIndex].indexV[2] - 1],
                                         &t, &u, &v)
            && (t < collisionData.t || collisionData.t == 0.0))
    {
        collisionData.t = t;
        collisionData.u = u;
        collisionData.v = v;
        collisionData.vn0 = node->obj3d->vertices->vn[node->obj3d->faces3[node->faceIndex].indexVn[0]-1];
        collisionData.vn1 = node->obj3d->vertices->vn[node->obj3d->faces3[node->faceIndex].indexVn[1]-1];
        collisionData.vn2 = node->obj3d->vertices->vn[node->obj3d->faces3[node->faceIndex].indexVn[2]-1];
        collisionData.normal = node->obj3d->vertices->vn[node->obj3d->faces3[node->faceIndex].indexVn[0]-1];
        collisionData.material = node->obj3d->material;
    }
}

/*void CastRay::browseTree(const Ray &ray, const treeNode_t *node, collisionData_t &collisionData)
{
    Obj3d *obj3d = nullptr;
    double t, u, v;

    if (!node->obj3d)
    {
        if (!CastRay::aabb_raycast(node->bBox, ray))
            return;
        if (node->nxt1)
            CastRay::browseTree(ray, node->nxt1, collisionData);
        if (node->nxt2)
            CastRay::browseTree(ray, node->nxt2, collisionData);
    }
    else
    {
        obj3d = static_cast<Obj3d *>(node->obj3d);
        if (CastRay::triangle_raycast(ray,
                                      obj3d->vertices->v[obj3d->faces3[node->faceIndex].indexV[0] - 1],
                                      obj3d->vertices->v[obj3d->faces3[node->faceIndex].indexV[1] - 1],
                                      obj3d->vertices->v[obj3d->faces3[node->faceIndex].indexV[2] - 1],
                                      &t, &u, &v))
        {
            if (collisionData.t == 0.0 || t < collisionData.t)
            {
                collisionData.t = t;
                collisionData.u = u;
                collisionData.v = v;
                collisionData.normal = node->obj3d->vertices->vn[node->obj3d->faces3[node->faceIndex].indexVn[0]-1];
            }
        }
    }
}*/

Vector3d CastRay::normalInterpolation(const collisionData_t &collisionData)
{
    double u = collisionData.u;
    double v = collisionData.v;
    double w = 1.0-u-v;
    Vector3d iVn;

    iVn = (collisionData.vn1*u + collisionData.vn2*v + collisionData.vn0*w);
    iVn.normalise();
    return (iVn);
}

bool CastRay::castRay(const Ray &ray, const treeNode_t *node, collisionData_t &collisionData)
{
    CastRay::browseTree(ray, node, collisionData);
    if (collisionData.t <= 0.0)
        return (false);
    collisionData.position = ray.origin + ray.direction*collisionData.t;
    collisionData.normal = CastRay::normalInterpolation(collisionData);
    //if (ray.direction.dotProduct(collisionData.normal) >= 0.0)
        //collisionData.normal *= -1.0;
    return (true);
}
