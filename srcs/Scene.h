#ifndef SCENE_H
#define SCENE_H

#include <thread>
#include <vector>
#include "FileImport.h"
#include "Camera.h"
#include "Obj3d.h"
#include "CollisionTree.h"
#include "Benchmark.h"

struct mesh_t
{
    vertices_t vertices;
    std::vector<Obj3d *> objs;
    std::map<std::string, Material *> materials;
    Material defaultMaterial;
    treeNode_t *collisionTree = nullptr;
};

class Scene
{
public:
    Scene();
    ~Scene();

public:
    bool loadFile(const std::string &path);
    void buidTree();

private:
    void freeMesh();

public:
    Camera *_camera;
    struct mesh_t _mesh;
    int _samples;
    int _maxDepth;
    size_t _totalThreads;
};

#endif // SCENE_H
