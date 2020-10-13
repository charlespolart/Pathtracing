#ifndef COLLISIONTREE_H
#define COLLISIONTREE_H

#include <algorithm>
#include <thread>
#include <mutex>
#include <iostream>
#include "Vector.h"
#include "Obj3d.h"

struct boundingBox_t
{
    Vector3d topRight;
    Vector3d bottomLeft;
    Vector3d bounds[2];
};

struct treeNode_t
{
    struct treeNode_t *nxt1 = nullptr;
    struct treeNode_t *nxt2 = nullptr;
    Obj3d *obj3d = nullptr;
    size_t faceIndex = 0;
    boundingBox_t *bBox = nullptr;
};

class CollisionTree
{
public:
    static void freeTree(treeNode_t *node);
    static treeNode_t *build(std::vector<Obj3d *> &objs, int threads);
    static void buildMultiThreads(std::vector<Obj3d *> &obj3ds, std::vector<treeNode_t *> &trees, size_t *index);

private:
    static boundingBox_t *createBoundingBox(const boundingBox_t *bBox1, const boundingBox_t *bBox2);
    static boundingBox_t *createBoundingBox(const face3_t &face, const std::vector<Vector3d> &vertices);
    static treeNode_t *buildTreeRoots(const std::vector<treeNode_t *> &leafs);
    static treeNode_t *buildTreeLeafs(Obj3d *obj);
};

#endif // COLLISIONTREE_H
