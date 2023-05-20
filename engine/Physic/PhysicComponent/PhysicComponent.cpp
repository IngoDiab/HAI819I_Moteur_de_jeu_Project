#include "PhysicComponent.h"
#include "engine/Objects/GameObject/GameObject.h"
#include "engine/Landscape/Landscape/Landscape.h"
#include "engine/Physic/PhysicManager/PhysicManager.h"

#include <glm/gtc/epsilon.hpp>
using namespace glm;

#define MIN_VELOCITY 0.01f
#define IS_AT_SAME_POS 0.001f
#define EPSILON_COLLISION 0.00001f

void PhysicComponent::PostConstructor()
{
    Component::PostConstructor();
    if(!mOwner) return;
    mCollider = mOwner->GetComponent<Collider>();
    mReadyToCollide = false;
}

void PhysicComponent::Destroy()
{
    PhysicManager* _physicManager = PhysicManager::Instance();
    _physicManager->RemovePhysiqueComponent(this);
    Component::Destroy();
}

void PhysicComponent::ApplyVelocity(const float _deltaTime)
{
    mLastPosition = mOwner->GetTransformInstance()->GetTransformData()->mLocalPosition;

    //Forces
    mAcceleration = mForces/mMass;
    mForces = vec3(0);

    //Gravity
    if(mHasGravity) mAcceleration += mGravityDirection * mGravity;

    //Velocity
    mVelocity += mAcceleration * _deltaTime;
    
    //Friction
    mAcceleration.x -= mAcceleration.x*(1-mFriction)* _deltaTime;
    mAcceleration.z -= mAcceleration.z*(1-mFriction)* _deltaTime;
    mVelocity.x -= mVelocity.x*(1-mFriction)* _deltaTime;
    mVelocity.z -= mVelocity.z*(1-mFriction)* _deltaTime;

    if(length(mAcceleration) < MIN_VELOCITY) mAcceleration = vec3(0);
    if(length(mVelocity) < MIN_VELOCITY) mVelocity = vec3(0);

    if(mMaxVelocitySpeed >= 0 && length(mVelocity) > mMaxVelocitySpeed)
    mVelocity = normalize(mVelocity) * mMaxVelocitySpeed;

    //Update position
    vec3 _newPosition = mLastPosition + mVelocity*_deltaTime;

    mOwner->SetPosition(_newPosition);
}

void PhysicComponent::ApplyClip()
{
    if(!mClipToLandscape) return;
    vec3 _position = mOwner->GetWorldPosition();
    vec3 _projected = _position;
    mClipToLandscape->GetProjectionOnPlane(_projected,mOffsetClip);
    if(!mActiveClip && _position.y < _projected.y - 0.01f)
    {
        EnableGravity(false);
        ActiveClip(true);
        mVelocity = vec3(0);
    }
    if(mActiveClip) mOwner->SetPosition(_projected);
}

float PhysicComponent::ProjectedHeight()
{
    vec3 _projectedPosition;
    mClipToLandscape->GetProjectionOnPlane(_projectedPosition,mOffsetClip);
    return _projectedPosition.y;
}

void PhysicComponent::ResponseCollision(const float _deltaTime, const vec3& _normal, const float _penetration)
{
    vec3 _posBeforeAdjustement = mOwner->GetTransformInstance()->GetTransformData()->mWorldPosition;
    vec3 _posAfterAdjustement = _posBeforeAdjustement + _normal*_penetration + _normal*EPSILON_COLLISION;
    mOwner->SetPosition(_posAfterAdjustement);
    if(mBounciness == 0) StopAccelVelOnCollide(_normal);
    else BounceOnCollide(_normal);
    mPosPreviousFrame = _posAfterAdjustement;
}

void PhysicComponent::StopAccelVelOnCollide(const vec3& _normal)
{
    if(_normal.x > 0+EPSILON_COLLISION)
    {
        mAcceleration.x = std::max(mAcceleration.x, 0.f);
        mVelocity.x = std::max(mVelocity.x, 0.f);
    }

    if(_normal.x < 0-EPSILON_COLLISION)
    {
        mAcceleration.x = std::min(mAcceleration.x, 0.f);
        mVelocity.x = std::min(mVelocity.x, 0.f);
    }

    if(_normal.y > 0+EPSILON_COLLISION)
    {
        mAcceleration.y = std::max(mAcceleration.y, 0.f);
        mVelocity.y = std::max(mVelocity.y, 0.f);
    }
    if(_normal.y < 0-EPSILON_COLLISION)
    {
        mAcceleration.y = std::min(mAcceleration.y, 0.f);
        mVelocity.y = std::min(mVelocity.y, 0.f);
    }

    if(_normal.z > 0+EPSILON_COLLISION)
    {
        mAcceleration.z = std::max(mAcceleration.z, 0.f);
        mVelocity.z = std::max(mVelocity.z, 0.f);
    }

    if(_normal.z < 0-EPSILON_COLLISION)
    {
        mAcceleration.z = std::min(mAcceleration.z, 0.f);
        mVelocity.z = std::min(mVelocity.z, 0.f);
    }
}

void PhysicComponent::BounceOnCollide(const vec3& _normal)
{
    vec3 _incidentVelocity = normalize(mVelocity);
    vec3 _incidentAcceleration = normalize(mAcceleration);

    vec3 _isVelNull = epsilonEqual(mVelocity, vec3(0), MIN_VELOCITY);
    vec3 _isAccNull = epsilonEqual(mAcceleration, vec3(0), MIN_VELOCITY);

    float _dotVelocityNormal = dot(_incidentVelocity, _normal);
    float _dotAccNormal = dot(_incidentAcceleration, _normal);
    
    vec3 _maskPos = mOwner->GetTransformInstance()->GetTransformData()->mWorldPosition * _normal;
    vec3 _maskPrevious = mPosPreviousFrame * _normal;

    vec3 _isEqual = epsilonEqual(_maskPos, _maskPrevious, IS_AT_SAME_POS);
    if(_isEqual.x && _isEqual.y && _isEqual.z)
    {
        StopAccelVelOnCollide(_normal);
        return;
    }

    float _dotIncidentVelNormal = dot(_incidentVelocity, _normal);
    float _dotIncidentAccNormal = dot(_incidentAcceleration, _normal);
        
    vec3 _bouncedVelocity = _dotIncidentVelNormal>=1-IS_AT_SAME_POS ? _incidentVelocity + _incidentVelocity *mBounciness: normalize(_incidentVelocity - 2*dot(_incidentVelocity, _normal)*_normal);
    vec3 _bouncedAcceleration = _dotIncidentAccNormal>=1-IS_AT_SAME_POS ? _incidentAcceleration + _incidentAcceleration* mBounciness: normalize(_incidentAcceleration - 2*dot(_incidentAcceleration, _normal)*_normal);

    mVelocity = (_isVelNull.x && _isVelNull.y && _isVelNull.z) ? _normal* mBounciness : _bouncedVelocity * length(mVelocity) * mBounciness;
    mAcceleration = (_isAccNull.x && _isAccNull.y && _isAccNull.z) ? _normal* mBounciness : _bouncedAcceleration * length(mAcceleration) * mBounciness;
}

void PhysicComponent::AddIgnoredCollisionType(const vector<COLLISION_TYPE>& _types)
{
    for(COLLISION_TYPE _type : _types)
        if(!IsIgnoring(_type)) mIgnoringCollisions.push_back(_type);
}

bool PhysicComponent::IsIgnoring(const COLLISION_TYPE _type)
{
    for(COLLISION_TYPE _typeIgnored : mIgnoringCollisions)
        if(_typeIgnored == _type) return true;
    return false;
}