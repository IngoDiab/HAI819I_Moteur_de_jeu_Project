#include "PhysicManager.h"

#include "engine/Physic/PhysicComponent/PhysicComponent.h"
#include "engine/Physic/BoxCollider/BoxCollider.h"
#include "engine/Physic/SphereCollider/SphereCollider.h"
#include "engine/Physic/CollisionData/CollisionData.h"
#include "engine/Meshs/Cube/Cube.h"

void PhysicManager::AddPhysicComponent(PhysicComponent* _physicComponent)
{
    BoxCollider* _box = dynamic_cast<BoxCollider*>(_physicComponent->GetCollider());
    if(_box)
    {
        mPhysicCubeComponents.push_back(PhysicCubeData(_physicComponent, _box));
        return;
    }

    SphereCollider* _sphere = dynamic_cast<SphereCollider*>(_physicComponent->GetCollider());
    if(_sphere)
    {
        mPhysicSphereComponents.push_back(PhysicSphereData(_physicComponent, _sphere));
        return;
    }
}

void PhysicManager::DeletePhysicComponents()
{
    mPhysicCubeComponents.clear();
    mPhysicSphereComponents.clear();
}

void PhysicManager::UpdatePhysic(const float _deltaTime)
{
    mTimer+=_deltaTime;
    float _dtPhysic = 1.0f/(float)mFPSPhysic;
    if(mTimer < _dtPhysic) return;
    mTimer = 0;
    ApplyVelocity(_dtPhysic);
    ClipPhysicComponents();
    DetectCollisions();
    ResolveCollisions(_dtPhysic);
    EndProcessCallbacks();
}

void PhysicManager::ApplyVelocity(const float _deltaTime)
{
    for(PhysicCubeData _dataCube : mPhysicCubeComponents)
        _dataCube.mPhysicComponent->ApplyVelocity(_deltaTime);

    for(PhysicSphereData _dataSphere : mPhysicSphereComponents)
        _dataSphere.mPhysicComponent->ApplyVelocity(_deltaTime);
}

void PhysicManager::ClipPhysicComponents()
{
    for(PhysicCubeData _dataCube : mPhysicCubeComponents)
        _dataCube.mPhysicComponent->ApplyClip();

    for(PhysicSphereData _dataSphere : mPhysicSphereComponents)
        _dataSphere.mPhysicComponent->ApplyClip();
}

void PhysicManager::DetectCollisions()
{
    //Cube collide
    for(PhysicCubeData _dataCubeMain : mPhysicCubeComponents)
    {
        if(!_dataCubeMain.mPhysicComponent->IsReadyToCollide()) continue;
        BoxCollider* _colliderMain = _dataCubeMain.mBoxCollider;

        //with cube
        for(PhysicCubeData _dataCubeOther : mPhysicCubeComponents)
        {
            if(!_dataCubeOther.mPhysicComponent->IsReadyToCollide()) continue;
            BoxCollider* _colliderOther = _dataCubeOther.mBoxCollider;
            if(_colliderMain == _colliderOther) continue;
            CollisionData _collision = _colliderMain->CollideCube(_colliderOther);
            if(!_collision.mAreColliding) continue;
            _collision.mMainComponent = _dataCubeMain.mPhysicComponent;
            _collision.mOtherComponent = _dataCubeOther.mPhysicComponent;
            mCollisionDetected.push_back(_collision);
        }

        //with sphere
        for(PhysicSphereData _dataSphereOther : mPhysicSphereComponents)
        {
            if(!_dataSphereOther.mPhysicComponent->IsReadyToCollide()) continue;
            SphereCollider* _colliderOther = _dataSphereOther.mSphereCollider;
            //if(_colliderMain == _colliderOther) continue;
            CollisionData _collision = _colliderMain->CollideSphere(_colliderOther);
            if(!_collision.mAreColliding) continue;
            _collision.mMainComponent = _dataCubeMain.mPhysicComponent;
            _collision.mOtherComponent = _dataSphereOther.mPhysicComponent;
            mCollisionDetected.push_back(_collision);
        }
    }

    //Sphere collide
    for(PhysicSphereData _dataSphereMain : mPhysicSphereComponents)
    {
        if(!_dataSphereMain.mPhysicComponent->IsReadyToCollide()) continue;
        SphereCollider* _colliderMain = _dataSphereMain.mSphereCollider;

        //with cube
        for(PhysicCubeData _dataCubeOther : mPhysicCubeComponents)
        {
            if(!_dataCubeOther.mPhysicComponent->IsReadyToCollide()) continue;
            BoxCollider* _colliderOther = _dataCubeOther.mBoxCollider;
            //if(_colliderMain == _colliderOther) continue;
            CollisionData _collision = _colliderMain->CollideCube(_colliderOther);
            if(!_collision.mAreColliding) continue;
            _collision.mMainComponent = _dataSphereMain.mPhysicComponent;
            _collision.mOtherComponent = _dataCubeOther.mPhysicComponent;
            mCollisionDetected.push_back(_collision);
        }

        //with sphere
        for(PhysicSphereData _dataSphereOther : mPhysicSphereComponents)
        {
            if(!_dataSphereOther.mPhysicComponent->IsReadyToCollide()) continue;
            SphereCollider* _colliderOther = _dataSphereOther.mSphereCollider;
            if(_colliderMain == _colliderOther) continue;
            CollisionData _collision = _colliderMain->CollideSphere(_colliderOther);
            if(!_collision.mAreColliding) continue;
            _collision.mMainComponent = _dataSphereMain.mPhysicComponent;
            _collision.mOtherComponent = _dataSphereOther.mPhysicComponent;
            mCollisionDetected.push_back(_collision);
        }
    }
}

void PhysicManager::ResolveCollisions(const float _deltaTime)
{
    for(CollisionData _data : mCollisionDetected)
    {
        PhysicComponent* _mainComponent =  _data.mMainComponent;
        PhysicComponent* _otherComponent =  _data.mOtherComponent;

        Collider* _mainCollider = _mainComponent->GetCollider();
        Collider* _otherCollider = _otherComponent->GetCollider();

        bool _mainIsTrigger = _mainCollider->IsTrigger();
        bool _otherIsTrigger = _otherCollider->IsTrigger();

        if(!_mainIsTrigger && !_otherIsTrigger)
        {
            if(!_mainComponent->IsStatic()) _mainComponent->ResponseCollision(_deltaTime,_data.mImpactNormale, _data.mAmountInCollision);
            if(!_mainComponent->IsStatic() || !_otherComponent->IsStatic()) _mainCollider->ProcessCollideCallbacks(_otherCollider, _data);
        }
        else if(_mainIsTrigger)
        {
            if(!_mainComponent->IsStatic() || !_otherComponent->IsStatic()) _mainCollider->ProcessTriggerCallbacks(_otherCollider, _data);
        }

    }

    //Empty Collisions
    mCollisionDetected.clear();
}

void PhysicManager::EndProcessCallbacks()
{
    for(PhysicCubeData _dataCube : mPhysicCubeComponents)
        _dataCube.mPhysicComponent->GetCollider()->EndProcessCallbacks();

    for(PhysicSphereData _dataSphere : mPhysicSphereComponents)
        _dataSphere.mPhysicComponent->GetCollider()->EndProcessCallbacks();
}