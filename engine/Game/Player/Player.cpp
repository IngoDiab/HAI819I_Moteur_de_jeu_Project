#include "Player.h"

#include <iostream>

Player::Player()
{
    mMeshComponent = AddComponent<MeshComponent>(vec3(0), vec3(0), vec3(.1));
    mMeshComponent->CreateMesh<Mesh>("3DModels/Asteroid/scene.gltf");
    mMeshComponent->CreateMaterial<Material>(PHONG_VERTEX, PHONG_FRAG);

    mBoxCollider = AddComponent<BoxCollider>();
    mBoxCollider->SetSize(vec3(10));

    mPhysicComponent = AddComponent<PhysicComponent>();
    mPhysicComponent->EnableGravity(false);


    ObjectManager* _objectManager = ObjectManager::Instance();
    mCamera = _objectManager->Create<Camera>(vec3(0,0,-50), vec3(0), vec3(1),this);

    Engine::Instance()->SetViewportCamera(mCamera);

    forwardThrust = 2;

    InputManager* _inputManager = InputManager::Instance();
    _inputManager->BindAxis({{GLFW_KEY_UP,GLFW_KEY_DOWN}}, this, (void* (Object::*)(float))&Player::ApplyThrustForward);
}

void Player::ApplyThrustForward(float force)
{
    //cout << "PLayer" <<  mTransform.GetPosition().x << "  " << mTransform.GetPosition().y << "  " << mTransform.GetPosition().z << //endl;
    //cout << "Camera" <<  mCamera->GetWorldPosition().x << "  " << mCamera->GetWorldPosition().y << "  " << mCamera->GetWorldPosition().z << endl;
    //cout << mPhysicComponent->GetVelocity().x << "  " <<  mPhysicComponent->GetVelocity().y << "  " <<  mPhysicComponent->GetVelocity().z << endl;
    mPhysicComponent->AddVelocity(mTransform.GetForwardVector() * forwardThrust * force * Engine::Instance()->DeltaTime());
}
