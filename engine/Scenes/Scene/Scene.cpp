#include "Scene.h"
#include "engine/Camera/Camera/Camera.h"

Scene::~Scene()
{
    UnloadScene();
}

void Scene::UnloadScene()
{
    ObjectManager* _objectManager = ObjectManager::Instance();   
    _objectManager->DeleteObjects();

    ShaderManager* _shaderManager = ShaderManager::Instance();
    _shaderManager->DeleteAllShaders();

    delete mSkybox;
}

void Scene::Update(const float _deltaTime)
{
    ObjectManager* _objectManager = ObjectManager::Instance();
    const float _sceneDeltaTime = _deltaTime*mTickSpeed;
    _objectManager->TickObjects(_sceneDeltaTime);
}

void Scene::LateUpdate(const float _deltaTime)
{
    ObjectManager* _objectManager = ObjectManager::Instance();
    const float _sceneDeltaTime = _deltaTime*mTickSpeed;
    _objectManager->TickLateObjects(_sceneDeltaTime);
}

void Scene::DrawSkybox(Camera* _camera)
{
    if(mSkybox) mSkybox->Draw(_camera);
}