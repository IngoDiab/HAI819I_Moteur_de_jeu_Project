#include "Ground_Player.h"
#include "engine/Planets/Planet/Planet.h"
#include "engine/Engine/Engine.h"
#include "engine/Meshs/Sphere/Sphere.h"
#include "engine/Materials/Material.h"
#include "engine/Components/MeshComponent/MeshComponent.h"
#include "engine/Physic/PhysicComponent/PhysicComponent.h"
#include "engine/Physic/SphereCollider/SphereCollider.h"
#include "engine/Physic/BoxCollider/BoxCollider.h"

#include "engine/Game/Manager/GameManager.h"
#include "engine/Inputs/InputManager/InputManager.h"
#include "engine/FilesPath/FilesPath.h"

Ground_Player::Ground_Player()
{
    mMeshComponent = AddComponent<MeshComponent>(vec3(0), vec3(0), vec3(.1));
    mBoxCollider = AddComponent<BoxCollider>();
    mBoxCollider->SetSize(vec3(10,30,10));
    
    mPhysicComponent = AddComponent<PhysicComponent>();

    mPlayerCamera = CreatePlayerCamera();
    Engine::Instance()->SetViewportCamera(mPlayerCamera);

    mCanRotate = true;

    InputManager* _inputManager = InputManager::Instance();
    GameManager* _gm = GameManager::Instance();
    _inputManager->BindKey(GLFW_KEY_Q,ACTION_TYPE::PRESS, _gm, (void* (Object::*)(bool))&GameManager::SpaceTravel);
    _inputManager->BindKey(GLFW_KEY_LEFT_SHIFT,ACTION_TYPE::HOLD, this, (void* (Object::*)(bool))&Ground_Player::RunSpeed);
}

void Ground_Player::Update(const float _tickSpeed)
{
    GameObject::Update(_tickSpeed);
    UpdatePlayerSpeed(_tickSpeed);
}

void Ground_Player::UpdatePlayerSpeed(const float _tickSpeed)
{
    if(mMovementSpeed < mTargetSpeed) mMovementSpeed = (1-_tickSpeed*mAcceleration)*mMovementSpeed + _tickSpeed*mAcceleration*mTargetSpeed;
    else mMovementSpeed = (1-_tickSpeed*mDeceleration)*mMovementSpeed + _tickSpeed*mDeceleration*mTargetSpeed;
}

Camera* Ground_Player::CreatePlayerCamera()
{
    ObjectManager* _objectManager = ObjectManager::Instance();
    return _objectManager->Create<Camera>(vec3(0,20,0), vec3(0), vec3(1), this);
}

void Ground_Player::MoveLateral(const float _move)
{
    if(!mCanMove) return;
    const vec3 _currentPos = mTransform.GetPosition();
    mTransform.SetPosition(_currentPos+mTransform.GetRightVector()*_move*mMovementSpeed*Engine::Instance()->DeltaTime());
}

void Ground_Player::LateralVelocity(const float _move)
{
    if(!mCanMove) return;
    mPhysicComponent->AddVelocity(_move*mTransform.GetRightVector()*2.f);
}

void Ground_Player::MoveForwardBackward(const float _move)
{
    if(!mCanMove) return;
    const vec3 _currentPos = mTransform.GetPosition();
    mTransform.SetPosition(_currentPos+mTransform.GetForwardVector()*_move*mMovementSpeed*Engine::Instance()->DeltaTime());
}

void Ground_Player::ForwardBackwardVelocity(const float _move)
{
    if(!mCanMove) return;
    mPhysicComponent->AddVelocity(_move*mTransform.GetForwardVector()*2.f);
}

void Ground_Player::Jump(const bool _move)
{
    if(!_move) return;
    mPhysicComponent->EnableGravity(true);
    mPhysicComponent->ActiveClip(false);
    const vec3 _jumpDirection = normalize(mTransform.GetUpVector());
    mPhysicComponent->AddVelocity(_jumpDirection*mHeightJump);
}

void Ground_Player::MoveUpDown(const float _move)
{
    
}
    
void Ground_Player::RotateLocalAxisX(float _rotation)
{
    if(!mCanRotate)return;
    mPlayerCamera->RotateLocalAxisX(_rotation * mRotationSpeed*Engine::Instance()->DeltaTime());
}

void Ground_Player::RotateLocalAxisY(float _rotation)
{
    if(!mCanRotate)return;
    GameObject::RotateLocalAxisY(_rotation * mRotationSpeed*Engine::Instance()->DeltaTime());
}

void Ground_Player::RotateLocalAxisZ(float _rotation)
{
    if(!mCanRotate)return;
    GameObject::RotateLocalAxisZ(_rotation * mRotationSpeed*Engine::Instance()->DeltaTime());
}

void Ground_Player::ClipToLandscape(Landscape* const _landscape)
{
    if(!mPhysicComponent) return;
    mPhysicComponent->ActiveClip(true);
    mPhysicComponent->EnableGravity(false);
    mPhysicComponent->ClipObject(_landscape);
}

void Ground_Player::RunSpeed(const bool _pressed)
{
    mTargetSpeed = _pressed ? mRunSpeed : mWalkSpeed;
}