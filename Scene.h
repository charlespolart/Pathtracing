#ifndef SCENE_H
#define SCENE_H

#include <thread>
#include <vector>
#include "Camera.h"
#include "Obj3d.h"
#include "FileImport.h"
#include "CollisionTree.h"
#include "Benchmark.h"

enum renderingType_e
{
    RAYTRACING,
    PATHTRACING
};

struct mesh_t
{
    vertices_t vertices;
    std::vector<Obj3d *> objs;
    treeNode_t *collisionTree = nullptr;
};

class Scene
{
public:
    Scene();
    ~Scene();

public:
    void loadFile(const std::string &path);
    void buidTree();

private:
    void freeMesh();

public:
    Camera *camera;
    struct mesh_t mesh;
    size_t totalThreads;
    renderingType_e renderingType;
};

#endif // SCENE_H
