#include "SceneTP1.h"
#include "engine/Landscape/Landscape/Landscape.h"
#include "engine/Inputs/InputManager/InputManager.h"
#include "engine/Camera/EditorCamera/EditorCamera.h"
#include "engine/Camera/OrbitalCamera/OrbitalCamera.h"
#include "engine/Engine/Engine.h"

void SceneTP1::LoadScene()
{
    mLandscape = CreateLandscape();
    InitEditorCamera();
    InitOrbitalCamera(mLandscape);
    BindSceneInput();
    BindLandscapeInput(mLandscape);
}

void SceneTP1::UnloadScene()
{
    Scene::UnloadScene();
}

Landscape* SceneTP1::CreateLandscape()
{
    ObjectManager* _objectManager = ObjectManager::Instance();
    Landscape* _landscape = _objectManager->Create<Landscape>(new Landscape(vec3(0,20,0), vec3(0), vec3(200,1,200)));
    _landscape->ChangeResolution(16,16);
    _landscape->ApplyHeightmap("Textures/Heightmaps/Heightmap_Mountain.png",100);
    return _landscape;
}

void SceneTP1::InitEditorCamera() const
{
   EditorCamera::Instance()->SetPosition(vec3(0,200,-200));
}

void SceneTP1::InitOrbitalCamera(Landscape*& _landscape)
{
    ObjectManager* _objectManager = ObjectManager::Instance();
    mOrbitalCamera = _objectManager->Create<OrbitalCamera>(new OrbitalCamera(_landscape->GetTransform(), 300));
    mOrbitalCamera->SetMovementSpeed(20);

    InputManager* _inputManager = InputManager::Instance();
    _inputManager->BindAxis({{GLFW_KEY_D, GLFW_KEY_A}}, mOrbitalCamera, (void* (Object::*)(float))&OrbitalCamera::MoveLateral);
    _inputManager->BindAxis({{GLFW_KEY_SPACE, GLFW_KEY_LEFT_SHIFT}}, mOrbitalCamera, (void* (Object::*)(float))&OrbitalCamera::MoveUpDown);
}

void SceneTP1::BindSceneInput()
{
    InputManager* _inputManager = InputManager::Instance();
    _inputManager->BindKey(GLFW_KEY_C , ACTION_TYPE::PRESS, this, (void* (Object::*)(bool))&SceneTP1::TurnLandscapeOrbit);
}

void SceneTP1::BindLandscapeInput(Landscape*& _landscape) const
{
    InputManager* _inputManager = InputManager::Instance();
    _inputManager->BindAxis({{GLFW_KEY_UP,GLFW_KEY_DOWN}}, _landscape, (void* (Object::*)(float))&Landscape::ChangeSpeed);

    _inputManager->BindKey(GLFW_KEY_KP_ADD , ACTION_TYPE::HOLD, _landscape, (void* (Object::*)(bool))&Landscape::IncreaseResolution);
    _inputManager->BindKey(GLFW_KEY_KP_SUBTRACT, ACTION_TYPE::HOLD, _landscape, (void* (Object::*)(bool))&Landscape::DecreaseResolution);
}

void SceneTP1::TurnLandscapeOrbit(const bool _active)
{
    if(!_active) return;
    mIsLandscapeTurningOrbit = !mIsLandscapeTurningOrbit;
    mLandscape->ToggleRotation(_active);
    mIsLandscapeTurningOrbit ? Engine::Instance()->SetViewportCamera(mOrbitalCamera) : Engine::Instance()->SetViewportCamera(nullptr);
}
