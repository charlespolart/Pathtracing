#include "Scene.h"

Scene::Scene() :
    camera(new Camera),
    totalThreads(std::thread::hardware_concurrency()),
    renderingType(RAYTRACING)
{
}

Scene::~Scene()
{
    this->freeMesh();
    delete this->camera;
}

void Scene::freeMesh()
{
    for (size_t i = 0; i < this->mesh.objs.size(); ++i)
        delete this->mesh.objs[i];
    this->mesh = mesh_t{};
}

void Scene::loadFile(const std::string &path)
{
    Benchmark benchmark;

    this->freeMesh();
    FileImport::loadObj(path, this->mesh.objs, this->mesh.vertices);
}

void Scene::buidTree()
{
    this->mesh.collisionTree = CollisionTree::build(this->mesh.objs, this->totalThreads);
}
