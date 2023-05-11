#include "Planet.h"

#include "engine/Components/MeshComponent/MeshComponent.h"
#include "engine/Meshs/Sphere/Sphere.h"
#include "engine/Physic/PhysicComponent/PhysicComponent.h"
#include "engine/Physic/BoxCollider/BoxCollider.h"
#include "engine/Game/Manager/GameManager.h"
#include "engine/Objects/ObjectManager/ObjectManager.h"

Planet::Planet()
{
    mMeshComponent = AddComponent<MeshComponent>();
    mMeshComponent->CreateMesh<Sphere>();
    mMeshComponent->CreateMaterial<Material>(PHONG_VERTEX, PHONG_FRAG);

    mBoxCollider = AddComponent<BoxCollider>();
    mBoxCollider->SetSize(vec3(3));
    mBoxCollider->SetTrigger(false);
    // mBoxCollider->SetOnTriggerEnterCallback([&](CollisionData _data) 
    // {
    //     GameManager* _gameManager = GameManager::Instance();
    //     _gameManager->SetPlanetToEnter(this); 
    // });
    // mBoxCollider->SetOnTriggerExitCallback([&](CollisionData _data) 
    // {
    //     GameManager* _gameManager = GameManager::Instance();
    //     _gameManager->SetPlanetToEnter(nullptr); 
    // });

    mBoxCollider->SetOnCollisionCallback([&](CollisionData _data) 
    {
        ObjectManager* _objectManager = ObjectManager::Instance();
        _objectManager->Destroy(this); 
    });
    mPhysicComponent = AddComponent<PhysicComponent>();
    mPhysicComponent->EnableGravity(false);
    mPhysicComponent->ActiveClip(false);

    mPhysicComponent->SetCollisionType(COLLISION_TYPE::ASTEROID);
    mPhysicComponent->AddIgnoredCollisionType({COLLISION_TYPE::ASTEROID, COLLISION_TYPE::PLANET, COLLISION_TYPE::PLAYER});
}

void Planet::Update(const float _deltaTime)
{
    GameObject::Update(_deltaTime);
    // RotateAroundParent(_deltaTime);
    // RotateAroundAxis(_deltaTime);
}

void Planet::RotateAroundParent(const float _deltaTime)
{
    if(!mParent) return;
    mAngleRevolution += _deltaTime*mRevolutionSpeed;
    ClampAngle(mAngleRevolution, 0, 360);
    float _xPos = cos(radians(mAngleRevolution)) * mDistanceCenterRevolution;
    float _zPos = sin(radians(mAngleRevolution)) * mDistanceCenterRevolution;
    SetPosition(vec3(_xPos, 0, _zPos));
}

void Planet::RotateAroundAxis(const float _deltaTime)
{
    if(!mParent) return;
    mMeshComponent->GetTransformInstance()->RotateLocalAxisY(mRotationSpeed*_deltaTime);
}

void Planet::ClampAngle(float& _angle, const float _min, const float _max)
{
    _angle = _angle >= _max ? _angle-_max : _angle < _min ? _max + _angle : _angle;
}