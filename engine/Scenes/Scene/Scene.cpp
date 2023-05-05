#include "Scene.h"
#include "engine/Camera/Camera/Camera.h"
#include "engine/Inputs/InputManager/InputManager.h"
#include "engine/Physic/PhysicManager/PhysicManager.h"
#include "engine/Lights/LightManager/LightManager.h"

Scene::~Scene()
{
    UnloadScene();
}

void Scene::UnloadScene()
{
    InputManager* _inputManager = InputManager::Instance();
    _inputManager->DeleteObsoleteInputs();

    ShaderManager* _shaderManager = ShaderManager::Instance();
    _shaderManager->DeleteAllShaders();

    // Renderer* _renderer = Renderer::Instance();
    // _renderer->DeleteRenderables();

    ObjectManager* _objectManager = ObjectManager::Instance();   
    _objectManager->DeleteObjectsSpecificDurability(DURABILITY::SCENE);

    PhysicManager* _physicManager = PhysicManager::Instance();
    _physicManager->DeletePhysicComponents();

    // LightManager* _lightManager = LightManager::Instance();
    // _lightManager->DeleteLightsSpecificDurability(DURABILITY::SCENE);
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