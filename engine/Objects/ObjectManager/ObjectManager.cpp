#include "ObjectManager.h"

#include "engine/Camera/Camera/Camera.h"

void ObjectManager::TickObjects(const float _deltaTime)
{
    for(ITickable* _object : mTickableObject)
        _object->Update(_deltaTime*_object->GetTickSpeed());
}

void ObjectManager::DrawObjects(Camera* _camera)
{
    for(IRenderable* _object : mRenderableObjects)
        _object->Render(_camera);
}

void ObjectManager::DeleteObjects()
{
    for(ITickable* _object : mTickableObject)
        if(_object)
        {
            _object = nullptr;
            delete _object;
        }

    for(IRenderable* _object : mRenderableObjects)
    {
        _object->CleanRessources();
        if(_object)if(_object)
        {
            _object = nullptr;
            delete _object;
        }
    }
}