#include "Character.h"
#include "engine/Engine/Engine.h"
#include "engine/Meshs/Sphere/Sphere.h"
#include "engine/Materials/Material.h"
#include "engine/Components/MeshComponent/MeshComponent.h"
#include "engine/Physic/PhysicComponent/PhysicComponent.h"
#include "engine/Physic/SphereCollider/SphereCollider.h"
#include "engine/Physic/BoxCollider/BoxCollider.h"

#include "engine/FilesPath/FilesPath.h"

Character::Character()
{
    mMeshComponent = AddComponent<MeshComponent>(vec3(0), vec3(0), vec3(.1));
    mMeshComponent->CreateMesh<Mesh>("3DModels/Asteroid/scene.gltf");
    mMeshComponent->AddLOD<Sphere>(100, 10,10);
    mMeshComponent->AddLOD<Sphere>(200, 4,4);
    mMeshComponent->CreateMaterial<Material>(PHONG_VERTEX, PHONG_FRAG);
    //mSphereCollider = AddComponent<SphereCollider>();
    //mSphereCollider->SetRadius(7.5f);
    mBoxCollider = AddComponent<BoxCollider>();
    mBoxCollider->SetSize(vec3(10));
    // mBoxCollider->SetOnCollisionCallback([](CollisionData _data) 
    // {
    //     ObjectManager* _objectManager = ObjectManager::Instance();
    //     _objectManager->Create<GameObject>(_data.mImpactPosition); 
    // });
    mPhysicComponent = AddComponent<PhysicComponent>();
}

void Character::MoveLateral(const float _move)
{
    if(!mCanMove) return;
    const vec3 _currentPos = mTransform.GetPosition();
    mTransform.SetPosition(_currentPos+mTransform.GetRightVector()*_move*mMovementSpeed*Engine::Instance()->DeltaTime());
}

void Character::LateralVelocity(const float _move)
{
    if(!mCanMove) return;
    mPhysicComponent->AddVelocity(_move*mTransform.GetRightVector()*2.f);
}

void Character::MoveForwardBackward(const float _move)
{
    if(!mCanMove) return;
    const vec3 _currentPos = mTransform.GetPosition();
    mTransform.SetPosition(_currentPos+mTransform.GetForwardVector()*_move*mMovementSpeed*Engine::Instance()->DeltaTime());
}

void Character::ForwardBackwardVelocity(const float _move)
{
    if(!mCanMove) return;
    mPhysicComponent->AddVelocity(_move*mTransform.GetForwardVector()*2.f);
}

void Character::Jump(const bool _move)
{
    if(!_move) return;
    const vec3 _jumpDirection = normalize(mTransform.GetUpVector());
    mPhysicComponent->AddVelocity(_jumpDirection*mHeightJump);
}

void Character::MoveUpDown(const float _move)
{

}
    
void Character::RotateLocalAxisX(float _rotation)
{

}

void Character::RotateLocalAxisY(float _rotation)
{

}

void Character::RotateLocalAxisZ(float _rotation)
{

}

void Character::ClipToLandscape(Landscape* const _landscape)
{
    if(!mPhysicComponent) return;
    mPhysicComponent->ClipObject(_landscape);
}