#pragma once

#include <vector>
using namespace std;

#include "engine/Utils/Singleton/Singleton.h"
#include "engine/Utils/Interfaces/ITickable.h"
#include "engine/Utils/Interfaces/IRenderable.h"

class Camera;

class ObjectManager final : public Singleton<ObjectManager>
{
    vector<ITickable*> mTickableObject = vector<ITickable*>();
    vector<IRenderable*> mRenderableObjects = vector<IRenderable*>();

public:
    void TickObjects(const float _deltaTime);
    void DrawObjects(Camera* _camera);
    void DeleteObjects();

public:
    template<typename T>
    T* Create(T* _object);
};

template<typename T>
T* ObjectManager::Create(T* _object)
{
    IRenderable* _castRenderable = dynamic_cast<IRenderable*>(_object);
    if(_castRenderable) mRenderableObjects.push_back(_castRenderable);

    ITickable* _castTickable = dynamic_cast<ITickable*>(_object);
    if(_castTickable) mTickableObject.push_back(_castTickable);

    if(!_castRenderable && !_castTickable) 
    {
        delete _object;
        return nullptr;
    }
    return _object;
}