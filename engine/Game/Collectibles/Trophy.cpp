#include "Trophy.h"

#include "engine/Components/MeshComponent/MeshComponent.h"
#include "engine/Physic/PhysicComponent/PhysicComponent.h"
#include "engine/Physic/BoxCollider/BoxCollider.h"

#include "engine/Objects/ObjectManager/ObjectManager.h"


Trophy::Trophy()
{
    mMeshComponent = AddComponent<MeshComponent>(vec3(0), vec3(0), vec3(7));
    mMeshComponent->CreateMesh<Mesh>("3DModels/Trophy/Trophy.glb", false);
    mMeshComponent->CreateMaterial<Material>();
    Material* _material = mMeshComponent->GetMaterial(0);
    _material->SetTexture(TEXTURE_SLOT::ALBEDO, "3DModels/Trophy/Textures/Albedo.png");

    mBoxCollider = AddComponent<BoxCollider>();
    mBoxCollider->SetTrigger(true);
    mBoxCollider->SetCenter(vec3(0,20,0));
    mBoxCollider->SetSize(vec3(30,50,30));

    mPhysicComponent = AddComponent<PhysicComponent>();
    mPhysicComponent->EnableGravity(false);

    mCanRotate = true;

    mPhysicComponent->SetCollisionType(COLLISION_TYPE::TROPHY);
    mPhysicComponent->AddIgnoredCollisionType({COLLISION_TYPE::PLANET, COLLISION_TYPE::ASTEROID, COLLISION_TYPE::PROJECTILE});
}

void Trophy::Update(const float _tickSpeed)
{
    GameObject::Update(_tickSpeed);
    RotateLocalAxisY(mRotationSpeed*_tickSpeed);
}

void Trophy::RotateLocalAxisX(const float _rotation)
{
}

void Trophy::RotateLocalAxisY(const float _rotation)
{
    if(!mCanRotate) return;
    mMeshComponent->GetTransformInstance()->RotateLocalAxisY(_rotation);
}

void Trophy::RotateLocalAxisZ(const float _rotation)
{
}