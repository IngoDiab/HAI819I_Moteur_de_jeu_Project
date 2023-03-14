#include "Renderer.h"
#include "engine/Camera/Camera/Camera.h"
#include "engine/Objects/ObjectManager/ObjectManager.h"

void Renderer::AddRenderable(IRenderable* _renderable)
{
    mRenderableObjects.push_back(_renderable);
}

void Renderer::DrawObjects(Camera* _camera)
{
    for(IRenderable* _object : mRenderableObjects)
        _object->Render(_camera);
}

void Renderer::Draw3DAxis()
{
    vector<GameObject*> _sceneGO = ObjectManager::Instance()->GetGameObjects();
    for(GameObject* _object : _sceneGO)
        _object->Draw3DAxis();
}