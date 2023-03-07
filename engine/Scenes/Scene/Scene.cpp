#include "Scene.h"
#include "engine/Camera/Camera/Camera.h"

Scene::~Scene()
{
    UnloadScene();
}

void Scene::UnloadScene()
{
    mObjectManager.DeleteObjects();
    mShaderManager.DeleteAllShaders();
}

void Scene::Update(const float _deltaTime)
{
    const float _sceneDeltaTime = _deltaTime*mTickSpeed;
    mObjectManager.TickObjects(_sceneDeltaTime);
}

void Scene::DrawSkybox(Camera* _camera)
{
    mSkybox.Draw(_camera);
}


void Scene::DrawScene(Camera* _camera)
{
    mObjectManager.DrawObjects(_camera);
}