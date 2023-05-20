#include "Projectile.h"
#include "engine/Components/MeshComponent/MeshComponent.h"
#include "engine/Meshs/Cube/Cube.h"
#include "engine/Physic/PhysicComponent/PhysicComponent.h"
#include "engine/Physic/BoxCollider/BoxCollider.h"

#include "engine/Game/Manager/GameManager.h"
#include "engine/Objects/ObjectManager/ObjectManager.h"
#include "engine/FilesPath/FilesPath.h"

Projectile::Projectile()
{
    mMeshComponent = AddComponent<MeshComponent>(vec3(0), vec3(0), vec3(.25,.25,5));
    mMeshComponent->CreateMesh<Cube>();
    Material* _material = mMeshComponent->CreateMaterial<Material>(PHONG_VERTEX, PHONG_FRAG);
    _material->SetValueCoefficients(COEFF_SLOT::EMISSIVNESS, 1);

    mBoxCollider = AddComponent<BoxCollider>();
    mBoxCollider->SetSize(vec3(.25,.25,5));
    mBoxCollider->SetCenter(vec3(0,0,0));

    mBoxCollider->SetOnCollisionCallback([&](CollisionData _data) 
    {
        ObjectManager* _objectManager = ObjectManager::Instance();
        _objectManager->Destroy(this); 
    });

    mPhysicComponent = AddComponent<PhysicComponent>();
    mPhysicComponent->EnableGravity(false);
    mPhysicComponent->SetFriction(1);
    mPhysicComponent->SetMaxVelocity(-1);
    mPhysicComponent->SetCollisionType(COLLISION_TYPE::PROJECTILE);
    mPhysicComponent->AddIgnoredCollisionType({COLLISION_TYPE::PLAYER, COLLISION_TYPE::PROJECTILE, COLLISION_TYPE::TROPHY});
}

void Projectile::Launch(const vec3& _direction, const float _power)
{
    mPhysicComponent->SetVelocity(_direction*_power);
}