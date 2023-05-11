#pragma once

#include <vector>
using namespace std;

#include "engine/Utils/Singleton/Singleton.h"
#include "engine/Physic/CollisionData/CollisionData.h"

class PhysicComponent;
class BoxCollider;
class SphereCollider;

struct PhysicData
{
    PhysicComponent* mPhysicComponent = nullptr;
    PhysicData(){}
    PhysicData(PhysicComponent* _component) : mPhysicComponent(_component){}
};

struct PhysicCubeData : public PhysicData
{
    BoxCollider* mBoxCollider = nullptr;
    PhysicCubeData(){}
    PhysicCubeData(PhysicComponent* _component, BoxCollider* _box) : PhysicData(_component), mBoxCollider(_box){}

    bool operator==(const PhysicCubeData _other)
    {
        return mPhysicComponent == _other.mPhysicComponent;
    }
};

struct PhysicSphereData : public PhysicData
{
    SphereCollider* mSphereCollider = nullptr;
    PhysicSphereData(){}
    PhysicSphereData(PhysicComponent* _component, SphereCollider* _sphere) : PhysicData(_component), mSphereCollider(_sphere){}

    bool operator==(const PhysicSphereData _other)
    {
        return mPhysicComponent == _other.mPhysicComponent;
    }
};

class PhysicManager final : public Singleton<PhysicManager>
{
    int mFPSPhysic = 200;
    float mTimer = 0;
    vector<PhysicCubeData> mPhysicCubeComponents = vector<PhysicCubeData>();
    vector<PhysicSphereData> mPhysicSphereComponents = vector<PhysicSphereData>();
    vector<CollisionData> mCollisionDetected = vector<CollisionData>();

public:
    void AddPhysicComponent(PhysicComponent* _physicComponent);
    void RemovePhysiqueComponent(PhysicComponent* _physicComponent);
    void DeletePhysicComponents();

public:
    void UpdatePhysic(const float _deltaTime);

private:
    void ApplyVelocity(const float _deltaTime);
    void ClipPhysicComponents();

    void DetectCollisions();
    void ResolveCollisions(const float _deltaTime);
    void EndProcessCallbacks();
};