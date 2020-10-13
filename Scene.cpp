#include "Scene.h"

Scene::Scene() :
    _camera(new Camera),
    _samples(0),
    _maxDepth(5),
    _totalThreads(std::thread::hardware_concurrency())
{
}

Scene::~Scene()
{
    this->freeMesh();
    delete this->_camera;
}

void Scene::freeMesh()
{
    for (size_t i = 0; i < this->_mesh.objs.size(); ++i)
        delete this->_mesh.objs[i];
    for (std::map<std::string, Material *>::iterator it = this->_mesh.materials.begin(); it != this->_mesh.materials.end(); ++it)
        delete it->second;
    this->_mesh.materials.clear();
    this->_mesh = mesh_t{};
}

bool Scene::loadFile(const std::string &path)
{
    this->freeMesh();
    return (FileImport::loadObj(path, this->_mesh.objs, this->_mesh.vertices, this->_mesh.materials, &this->_mesh.defaultMaterial));
}

void Scene::buidTree()
{
    this->_mesh.collisionTree = CollisionTree::build(this->_mesh.objs, this->_totalThreads);
}
