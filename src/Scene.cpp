#include "Scene.hh"

Scene::~Scene()
{
    for (auto &pair : this->objects)
    {
        delete pair.second;
    }
}

AbstractMobileObj *Scene::FindMobileObj(const char *sName)
{
    if (this->objects.count(sName) == 0)
    {
        return nullptr;
    }

    return this->objects[sName];
}

void Scene::AddMobileObj(AbstractMobileObj *pMobObj)
{
    if ((pMobObj == nullptr) || (this->objects.count(pMobObj->GetName())))
    {
        return;
    }

    this->objects[pMobObj->GetName()] = pMobObj;
}