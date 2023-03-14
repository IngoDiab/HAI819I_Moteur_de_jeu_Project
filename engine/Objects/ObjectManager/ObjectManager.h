#pragma once

#include <vector>
using namespace std;

#include "engine/Utils/Singleton/Singleton.h"
#include "engine/Objects/GameObject/GameObject.h"

class ObjectManager final : public Singleton<ObjectManager>
{
    vector<GameObject*> mSceneGameObjects = vector<GameObject*>();

public:
    void AddGameObject(GameObject* _object);
    void RemoveGameObject(GameObject* _object);
    void TickObjects(const float _deltaTime);
    void TickLateObjects(const float _deltaTime);
    bool Exist(GameObject* _object) const;
    void DeleteObjects();

public:
    vector<GameObject*> GetGameObjects() const {return mSceneGameObjects;}

public:
    template<typename T>
    T* Create(const vec3& _position = vec3(0), const vec3& _rotation = vec3(0), const vec3& _scale = vec3(1), GameObject* _parent = nullptr);
};

template<typename T>
T* ObjectManager::Create(const vec3& _position, const vec3& _rotation, const vec3& _scale, GameObject* _parent)
{
    T* _object = new T();
    GameObject* _gameobject = dynamic_cast<GameObject*>(_object);
    if(!_gameobject)
    {
        delete _object;
        return nullptr;
    }
    _gameobject->SetPosition(_position);
    _gameobject->SetRotation(_rotation);
    _gameobject->SetScale(_scale);
    if(!_parent) AddGameObject(_object);
    else _object->SetParent(_parent);
    return _object;
}