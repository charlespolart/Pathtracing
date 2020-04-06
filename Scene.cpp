#include "Scene.h"

Scene::Scene() :
    camera(new Camera),
    samples(0),
    maxDepth(5),
    totalThreads(std::thread::hardware_concurrency())
{
}

Scene::~Scene()
{
    this->freeMesh();
    for (size_t i = 0; i < this->mesh.materials.size(); ++i)
        delete this->mesh.materials[i];
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
    this->freeMesh();
    FileImport::loadObj(path, this->mesh.objs, this->mesh.vertices, &this->mesh.defaultMaterial);
}

void Scene::buidTree()
{
    this->mesh.collisionTree = CollisionTree::build(this->mesh.objs, this->totalThreads);
}
