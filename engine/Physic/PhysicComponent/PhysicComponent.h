#pragma once

#include "engine/Components/Component/Component.h"
#include "engine/Physic/CollisionData/CollisionData.h"

class Collider;
class Landscape;

class PhysicComponent : public Component
{
private:
    vec3 mPosPreviousFrame = vec3(0);
    vec3 mLastPosition = vec3(0);
    vec3 mGravityAcceleration = vec3(0);

protected:
    bool mReadyToCollide = false;
    Collider* mCollider = nullptr;
    vec3 mForces = vec3(0);
    vec3 mVelocity = vec3(0);
    vec3 mAcceleration = vec3(0);
    float mFriction = .2f;
    
    float mMass = 1;
    bool mHasGravity = true;
    vec3 mGravityDirection = vec3(0,-1,0);
    float mGravity = 9.81f;

    Landscape* mClipToLandscape = nullptr;
    float mOffsetClip = 10;

    bool mIsStatic = false;
    float mBounciness = .5f;

public:
    Collider* GetCollider() const {return mCollider;}
    bool IsReadyToCollide() const {return mReadyToCollide;}
    bool IsStatic() const {return mIsStatic;}
    float GetBounciness() const {return mBounciness;}

    void SetReadyToCollide(bool _ready) {mReadyToCollide = _ready;}
    void SetStatic(bool _static) {mIsStatic = _static;}

public:
    virtual void PostConstructor() override;

public:
    void ClipObject(Landscape* const _landscape) {mClipToLandscape = _landscape;}
    void AddForce(const vec3& _force) {mForces += _force;}
    void AddVelocity(const vec3& _velocity) {mVelocity += _velocity;}
    void SetVelocity(const vec3& _velocity) {mVelocity = _velocity;}
    void EnableGravity(const bool _enabled) {mHasGravity = _enabled;}

public :
    void ApplyVelocity(const float _deltaTime);
    void ApplyClip();
    
    void ResponseCollision(const float _deltaTime, const vec3& _normal, const float _penetration);
    void StopAccelVelOnCollide(const vec3& _normal);
    void BounceOnCollide(const vec3& _normal);
};