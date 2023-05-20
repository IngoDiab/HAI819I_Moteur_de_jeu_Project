#include "Asteroid.h"

#include "engine/Components/MeshComponent/MeshComponent.h"
#include "engine/Physic/PhysicComponent/PhysicComponent.h"
#include "engine/Physic/BoxCollider/BoxCollider.h"

#include "engine/Objects/ObjectManager/ObjectManager.h"


Asteroid::Asteroid()
{
    mMeshComponent = AddComponent<MeshComponent>(vec3(0), vec3(0), vec3(1));
    mMeshComponent->CreateMesh<Mesh>("3DModels/Asteroid/scene.gltf");

    mBoxCollider = AddComponent<BoxCollider>();
    mBoxCollider->SetSize(vec3(225));
    mBoxCollider->SetOnCollisionCallback([&](CollisionData _data) 
    {
        ObjectManager* _objectManager = ObjectManager::Instance();
        _objectManager->Destroy(this); 
    });

    mPhysicComponent = AddComponent<PhysicComponent>();
    mPhysicComponent->EnableGravity(false);
    mPhysicComponent->ActiveClip(false);
    mPhysicComponent->SetFriction(1);

    mPhysicComponent->SetCollisionType(COLLISION_TYPE::ASTEROID);
    mPhysicComponent->AddIgnoredCollisionType({COLLISION_TYPE::PLANET, COLLISION_TYPE::PLAYER, COLLISION_TYPE::TROPHY});

    mCanRotate = true;
}

void Asteroid::Update(const float _tickSpeed)
{
    GameObject::Update(_tickSpeed);
    RotateAroundAxis(_tickSpeed);
}

void Asteroid::RotateAroundAxis(const float _deltaTime)
{
    if(!mCanRotate) return;
    RotateLocalAxisX(mRotationSpeed*mRotationSpeedX*_deltaTime);
    RotateLocalAxisY(mRotationSpeed*mRotationSpeedY*_deltaTime);
    RotateLocalAxisZ(mRotationSpeed*mRotationSpeedZ*_deltaTime);
}

void Asteroid::RotateLocalAxisX(const float _rotation)
{
    mMeshComponent->GetTransformInstance()->RotateLocalAxisX(_rotation);
}

void Asteroid::RotateLocalAxisY(const float _rotation)
{
    mMeshComponent->GetTransformInstance()->RotateLocalAxisY(_rotation);
}

void Asteroid::RotateLocalAxisZ(const float _rotation)
{
    mMeshComponent->GetTransformInstance()->RotateLocalAxisZ(_rotation);
}