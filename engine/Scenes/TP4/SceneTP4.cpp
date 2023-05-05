#include "SceneTP4.h"
#include "engine/FilesPath/FilesPath.h"
#include "engine/Character/Character.h"
#include "engine/Landscape/Landscape/Landscape.h"
#include "engine/Landscape/Material/LandscapeMaterial.h"
#include "engine/Skyboxes/Skybox/Skybox.h"
#include "engine/Inputs/InputManager/InputManager.h"
#include "engine/Camera/EditorCamera/EditorCamera.h"
#include "engine/Components/MeshComponent/MeshComponent.h"
#include "engine/Engine/Engine.h"

void SceneTP4::LoadScene()
{
    Skybox* _skybox = Skybox::Instance();
    _skybox->ChangeSkybox("Textures/Skybox/Base/", ".jpg");

    mCharacter = CreateCharacter();
    mLandscape = CreateLandscape();

    InitEditorCamera();
    BindCharacterInput();
    BindLandscapeInput();
}

Character* SceneTP4::CreateCharacter()
{
    ObjectManager* _objectManager = ObjectManager::Instance();
    Character* _character = _objectManager->Create<Character>(vec3(0,25,0));

    MeshComponent* _meshComponent = _character->GetComponent<MeshComponent>();
    _meshComponent->GetTransformInstance()->RotateLocalAxisX(90);

    Material* _material = _meshComponent->GetMaterial(0);
    //_material->SetTexture(TEXTURE_SLOT::ALBEDO, "3DModels/DamagedHelmet/Textures/albedo.jpg");
    return _character;
}

Landscape* SceneTP4::CreateLandscape()
{
    ObjectManager* _objectManager = ObjectManager::Instance();
    Landscape* _landscape = _objectManager->Create<Landscape>(vec3(0,-50,0), vec3(0), vec3(10000,1,10000));
    _landscape->ChangeResolution(256,256);
    _landscape->ApplyHeightmap("Textures/Heightmaps/heightmap.png",1000000, 100);

    LandscapeMaterial* _landscapeMaterial= _landscape->GetMaterial();
    _landscapeMaterial->AddLayer(0, GRASS_TEXTURE);
    _landscapeMaterial->AddLayer(1, ROCK_TEXTURE);
    _landscapeMaterial->AddLayer(2, SNOWROCKS_TEXTURE);
    _landscapeMaterial->SetTiling(100);

    // _landscapeMaterial->AddTransition(0, 50);
    // _landscapeMaterial->AddTransition(1, 80);
    _landscapeMaterial->AddTransition(0, 70);
    _landscapeMaterial->AddTransition(1, 225);
    return _landscape;
}

void SceneTP4::InitEditorCamera() const
{
   EditorCamera::Instance()->SetPosition(vec3(0,10,-50));
}

void SceneTP4::BindCharacterInput()
{
    InputManager* _inputManager = InputManager::Instance();
    _inputManager->BindAxis({{GLFW_KEY_UP,GLFW_KEY_DOWN}}, mCharacter, (void* (Object::*)(float))&Character::ForwardBackwardVelocity);
    _inputManager->BindAxis({{GLFW_KEY_RIGHT,GLFW_KEY_LEFT}}, mCharacter, (void* (Object::*)(float))&Character::LateralVelocity);
    _inputManager->BindKey(GLFW_KEY_TAB, ACTION_TYPE::PRESS, mCharacter, (void* (Object::*)(bool))&Character::Jump);
}

void SceneTP4::BindLandscapeInput() const
{
    InputManager* _inputManager = InputManager::Instance();
    _inputManager->BindKey(GLFW_KEY_KP_ADD , ACTION_TYPE::HOLD, mLandscape, (void* (Object::*)(bool))&Landscape::IncreaseResolution);
    _inputManager->BindKey(GLFW_KEY_KP_SUBTRACT, ACTION_TYPE::HOLD, mLandscape, (void* (Object::*)(bool))&Landscape::DecreaseResolution);
}