#pragma once

#include "engine/Components/Component/Component.h"
#include "engine/Physic/CollisionData/CollisionData.h"

#include <vector>
using namespace std;

class Collider;
class Landscape;

enum class COLLISION_TYPE
{
    NOT_DEFINED,
    PLAYER,
    ASTEROID,
    PLANET,
    PROJECTILE,
    TROPHY
};

class PhysicComponent : public Component
{
    COLLISION_TYPE mCollisionType = COLLISION_TYPE::NOT_DEFINED;
    vector<COLLISION_TYPE> mIgnoringCollisions = vector<COLLISION_TYPE>();

    vec3 mPosPreviousFrame = vec3(0);
    vec3 mLastPosition = vec3(0);
    vec3 mGravityAcceleration = vec3(0);

protected:
    float mMaxVelocitySpeed = 200;

    bool mReadyToCollide = false;
    Collider* mCollider = nullptr;
    vec3 mForces = vec3(0);
    vec3 mVelocity = vec3(0);
    vec3 mAcceleration = vec3(0);
    float mFriction = .2f;
    
    float mMass = 1;
    bool mHasGravity = true;
    vec3 mGravityDirection = vec3(0,-1,0);
    float mGravity = 1000.1f;

    Landscape* mClipToLandscape = nullptr;
    float mOffsetClip = 10;
    bool mActiveClip = true;

    bool mIsStatic = false;
    float mBounciness = .5f;

public:
    COLLISION_TYPE GetCollisionType() const {return mCollisionType;}
    void SetCollisionType(const COLLISION_TYPE _type) { mCollisionType = _type;}

    Collider* GetCollider() const {return mCollider;}
    bool IsReadyToCollide() const {return mReadyToCollide;}
    bool IsStatic() const {return mIsStatic;}
    float GetBounciness() const {return mBounciness;}

    void SetMaxVelocity(float _max) { mMaxVelocitySpeed = _max;}

    void SetReadyToCollide(bool _ready) {mReadyToCollide = _ready;}
    void SetStatic(bool _static) {mIsStatic = _static;}
    void ActiveClip(bool _active) {mActiveClip = _active;}

public:
    virtual void PostConstructor() override;

public:
    void ClipObject(Landscape* const _landscape) {mClipToLandscape = _landscape;}
    void SetFriction(const float _friction) {mFriction = _friction;}
    void AddForce(const vec3& _force) {mForces += _force;}
    void AddVelocity(const vec3& _velocity) {mVelocity += _velocity;}
    void SetVelocity(const vec3& _velocity) {mVelocity = _velocity;}
    vec3 GetVelocity(){return mVelocity;}
    void EnableGravity(const bool _enabled) {mHasGravity = _enabled;}

public :
    void ApplyVelocity(const float _deltaTime);
    void ApplyClip();
    float ProjectedHeight();

    virtual void Destroy() override;
    
    void ResponseCollision(const float _deltaTime, const vec3& _normal, const float _penetration);
    void StopAccelVelOnCollide(const vec3& _normal);
    void BounceOnCollide(const vec3& _normal);

    void AddIgnoredCollisionType(const vector<COLLISION_TYPE>& _types);
    bool IsIgnoring(const COLLISION_TYPE _type);
};