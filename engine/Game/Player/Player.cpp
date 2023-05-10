#include "Player.h"

#include <iostream>

Player::Player()
{
    mMeshComponent = AddComponent<MeshComponent>(vec3(0,-1,3), vec3(0), vec3(.1));
    mMeshComponent->CreateMesh<Mesh>("3DModels/Spaceship/scene.gltf");
    mMeshComponent->CreateMaterial<Material>(PHONG_VERTEX, PHONG_FRAG);

    mBoxCollider = AddComponent<BoxCollider>();
    mBoxCollider->SetSize(vec3(1));

    mPhysicComponent = AddComponent<PhysicComponent>();
    mPhysicComponent->EnableGravity(false);


    ObjectManager* _objectManager = ObjectManager::Instance();
    mCamera = _objectManager->Create<Camera>(vec3(0,0,0), vec3(0), vec3(1),this);

    Engine::Instance()->SetViewportCamera(mCamera);

    InputManager* _inputManager = InputManager::Instance();

    _inputManager->BindAxis({{GLFW_KEY_UP,GLFW_KEY_DOWN}}, this, (void* (Object::*)(float))&Player::ApplyThrustForward);

    _inputManager->BindKey(GLFW_KEY_SPACE,ACTION_TYPE::HOLD, this, (void* (Object::*)(bool))&Player::Brake);

    _inputManager->BindAxis({{MOUSE_X,MOUSE_X}}, this, (void* (Object::*)(float))&Player::TurnY);
    _inputManager->BindAxis({{MOUSE_Y,MOUSE_Y}}, this, (void* (Object::*)(float))&Player::TurnX);
}

void Player::TurnX(float v)
{
    mTransform.RotateLocalAxisX(-v * mouseSensivity * Engine::Instance()->DeltaTime());
}

void Player::TurnY(float v)
{
    mTransform.RotateLocalAxisY(-v * mouseSensivity * Engine::Instance()->DeltaTime());
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
    mPhysicComponent->AddVelocity(mTransform.GetForwardVector() * forwardThrust * force * Engine::Instance()->DeltaTime());

    UpdateFOV();
}

void Player::UpdateFOV()
{
    float speedRatio = std::min(1.f,length(mPhysicComponent->GetVelocity()) / maxSpeedFOV);

    float fov = fovRange.x - ((fovRange.x-fovRange.y) * pow(speedRatio,fovRange.z));
    mCamera->SetFOV(fov);
}
