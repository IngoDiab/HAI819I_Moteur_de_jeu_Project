#include "ObjectManager.h"
#include <algorithm>
void ObjectManager::AddGameObject(GameObject* _object)
{
    if(Exist(_object)) return;
    mSceneGameObjects.push_back(_object);
}

void ObjectManager::RemoveGameObject(GameObject* _object)
{
    if(!Exist(_object)) return;
    mSceneGameObjects.erase(find(mSceneGameObjects.begin(), mSceneGameObjects.end(), _object));
}

void ObjectManager::TickObjects(const float _deltaTime)
{
    for(GameObject* _object : mSceneGameObjects)
        _object->Update(_deltaTime*_object->GetTickSpeed());
    for(GameObject* _object : mSceneGameObjects)
        _object->UpdateModelMatrix();
}

void ObjectManager::TickLateObjects(const float _deltaTime)
{
    for(GameObject* _object : mSceneGameObjects)
        _object->LateUpdate(_deltaTime*_object->GetTickSpeed());
}

bool ObjectManager::Exist(GameObject* _object) const
{
    for(GameObject* _objectInScene : mSceneGameObjects)
        if(_objectInScene == _object) return true;
    return false;
}

void ObjectManager::DeleteObjectsSpecificDurability(const DURABILITY _durability)
{
    vector<GameObject*> _GOToKeep;
    for(GameObject* _object : mSceneGameObjects)
    {   
        if(!_object) continue;
        if(_object->GetDurability() == _durability) delete _object;
        else _GOToKeep.push_back(_object);
    }
    mSceneGameObjects = _GOToKeep;
}

void ObjectManager::DeleteObjects()
{
    for(GameObject* _object : mSceneGameObjects)
        if(_object) delete _object;
    mSceneGameObjects.clear();
}