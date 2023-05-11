#include "Player.h"

#include <iostream>

#include "engine/Game/Manager/GameManager.h"
#include "engine/Game/Weapon/Projectile.h"
#include "engine/Physic/PhysicComponent/PhysicComponent.h"
#include "engine/Physic/BoxCollider/BoxCollider.h"
#include "engine/Components/MeshComponent/MeshComponent.h"
#include "engine/Camera/Camera/Camera.h"
#include "engine/Engine//Engine.h"

Player::Player()
{
    mMeshComponent = AddComponent<MeshComponent>(vec3(0,0,0), vec3(0), vec3(1));
    mMeshComponent->CreateMesh<Mesh>("3DModels/Spaceship/scene.gltf");

    int _nbMaterials = mMeshComponent->GetNbMaterials();
    for(int i = 0; i < _nbMaterials; ++i)
    {
        Material* _material = mMeshComponent->GetMaterial(i);
        if(!_material) return;
        _material->SetColor(COLOR_SLOT::AMBIENT, vec3(0.01f));
        _material->SetColor(COLOR_SLOT::SPECULAR, vec3(1));
        _material->SetValueCoefficients(COEFF_SLOT::SHININESS, 50);
    }

    mBoxCollider = AddComponent<BoxCollider>();
    mBoxCollider->SetSize(vec3(1));

    mPhysicComponent = AddComponent<PhysicComponent>();
    mPhysicComponent->EnableGravity(false);

    mPhysicComponent->SetCollisionType(COLLISION_TYPE::PLAYER);
    mPhysicComponent->AddIgnoredCollisionType({COLLISION_TYPE::PROJECTILE});


    ObjectManager* _objectManager = ObjectManager::Instance();
    mCamera = _objectManager->Create<Camera>(vec3(0,10,-30), vec3(0), vec3(1),this);
    Engine::Instance()->SetViewportCamera(mCamera);

    InputManager* _inputManager = InputManager::Instance();

    _inputManager->BindAxis({{GLFW_KEY_UP,GLFW_KEY_DOWN}}, this, (void* (Object::*)(float))&Player::ApplyThrustForward);

    _inputManager->BindKey(GLFW_KEY_SPACE,ACTION_TYPE::HOLD, this, (void* (Object::*)(bool))&Player::Brake);

    _inputManager->BindAxis({{MOUSE_X,MOUSE_X}}, this, (void* (Object::*)(float))&Player::TurnY);
    _inputManager->BindAxis({{MOUSE_Y,MOUSE_Y}}, this, (void* (Object::*)(float))&Player::TurnX);

    GameManager* _gm = GameManager::Instance();
    _inputManager->BindKey(GLFW_KEY_E,ACTION_TYPE::PRESS, _gm, (void* (Object::*)(bool))&GameManager::EnterPlanet);

    InitializeCanons();
}

void Player::InitializeCanons()
{
    ObjectManager* _objectManager = ObjectManager::Instance();
    mRightCanon =  _objectManager->Create<GameObject>(vec3(1.05,3,9.5), vec3(0), vec3(1),this);
    mLeftCanon =  _objectManager->Create<GameObject>(vec3(-1.05,3,9.5), vec3(0), vec3(1),this);

    InputManager* _inputManager = InputManager::Instance();
    _inputManager->BindKey(GLFW_MOUSE_BUTTON_LEFT,ACTION_TYPE::PRESS, this, (void* (Object::*)(bool))&Player::Shoot);
}

void Player::Shoot(bool _shootPressed)
{
    if(!_shootPressed) return;
    ObjectManager* _objectManager = ObjectManager::Instance();
    Projectile* _rightProjectile = _objectManager->Create<Projectile>(mRightCanon->GetWorldPosition(), mRightCanon->GetWorldRotation(), vec3(1));
    Projectile* _leftProjectile = _objectManager->Create<Projectile>(mLeftCanon->GetWorldPosition(), mLeftCanon->GetWorldRotation(), vec3(1));

    _rightProjectile->Launch(mRightCanon->GetTransform().mForwardVector, mShotPower);
    _leftProjectile->Launch(mRightCanon->GetTransform().mForwardVector, mShotPower);
}

void Player::TurnX(float v)
{
    mTransform.RotateLocalAxisX(v * mouseSensivity * Engine::Instance()->DeltaTime());
}

void Player::TurnY(float v)
{
    mTransform.RotateLocalAxisY(v * mouseSensivity * Engine::Instance()->DeltaTime());
}

void Player::Brake(bool b)
{
    float l = length(mPhysicComponent->GetVelocity());
    if(b && l > brakeLimit)
    {
        mPhysicComponent->AddVelocity(
            normalize(mPhysicComponent->GetVelocity()) *
            -std::max(brakeMinForce,pow(l*brakeRatio,brakeCurve) * brakeForce) *
            Engine::Instance()->DeltaTime());
    }
}

void Player::ApplyThrustForward(float force)
{
    //cout << "PLayer" <<  mTransform.GetPosition().x << "  " << mTransform.GetPosition().y << "  " << mTransform.GetPosition().z << //endl;
    //cout << "Camera" <<  mCamera->GetWorldPosition().x << "  " << mCamera->GetWorldPosition().y << "  " << mCamera->GetWorldPosition().z << endl;
    //cout << mPhysicComponent->GetVelocity().x << "  " <<  mPhysicComponent->GetVelocity().y << "  " <<  mPhysicComponent->GetVelocity().z << endl;
    mPhysicComponent->AddVelocity(mCamera->GetTransform().mForwardVector * forwardThrust * force * Engine::Instance()->DeltaTime());

    UpdateFOV();
}

void Player::UpdateFOV()
{
    float speedRatio = std::min(1.f,length(mPhysicComponent->GetVelocity()) / maxSpeedFOV);

    float fov = fovRange.x - ((fovRange.x-fovRange.y) * pow(speedRatio,fovRange.z));
    mCamera->SetFOV(fov);
}
