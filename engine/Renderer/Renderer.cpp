#include "Renderer.h"
#include "engine/Camera/Camera/Camera.h"
#include "engine/Objects/ObjectManager/ObjectManager.h"

void Renderer::AddRenderable(IRenderable* _renderable)
{
    mRenderableObjects.push_back(_renderable);
}

void Renderer::RemoveRenderable(IRenderable* _renderable)
{
    mRenderableObjects.erase(remove(mRenderableObjects.begin(), mRenderableObjects.end(), _renderable), mRenderableObjects.end());
}

void Renderer::DeleteRenderables()
{
    mRenderableObjects.clear();
}

void Renderer::DrawObjects(Camera* _camera)
{
    if(!_camera) return;
    for(IRenderable* _object : mRenderableObjects)
        if(_object)_object->Render(_camera);
}

void Renderer::Draw3DAxis()
{
    if(!mCanDraw3DAxis) return;
    vector<GameObject*> _sceneGO = ObjectManager::Instance()->GetGameObjects();
    for(GameObject* _object : _sceneGO)
        if(_object)_object->Draw3DAxis();
}