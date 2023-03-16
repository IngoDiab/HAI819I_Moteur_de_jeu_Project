#pragma once

#include <vector>
using namespace std;

#include "engine/Utils/Singleton/Singleton.h"
#include "engine/Objects/GameObject/GameObject.h"
#include "engine/Lights/LightManager/LightManager.h"
#include "engine/Lights/Light/Light.h"

class ObjectManager final : public Singleton<ObjectManager>
{
    vector<GameObject*> mSceneGameObjects = vector<GameObject*>();

public:
    void AddGameObject(GameObject* _object);
    void RemoveGameObject(GameObject* _object);
    void TickObjects(const float _deltaTime);
    void TickLateObjects(const float _deltaTime);
    bool Exist(GameObject* _object) const;
    void DeleteObjectsSpecificDurability(const DURABILITY _durability);
    void DeleteObjects();

public:
    vector<GameObject*> GetGameObjects() const {return mSceneGameObjects;}

public:
    template<typename T>
    T* Create(const vec3& _position = vec3(0), const vec3& _rotation = vec3(0), const vec3& _scale = vec3(1), GameObject* _parent = nullptr, DURABILITY _durability = DURABILITY::SCENE);
};

template<typename T>
T* ObjectManager::Create(const vec3& _position, const vec3& _rotation, const vec3& _scale, GameObject* _parent, DURABILITY _durability)
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
    _gameobject->SetDurability(_durability);
    if(!_parent) AddGameObject(_object);
    else _object->SetParent(_parent);

    Light* _light = dynamic_cast<Light*>(_object);
    if(_light)
    {
        LightManager::Instance()->AddLight(_light);
    }

    return _object;
}