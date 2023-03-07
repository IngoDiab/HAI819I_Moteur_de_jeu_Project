#include "OrbitalCamera.h"
#include "engine/Engine/Engine.h"
#include "engine/Transform/Transform.h"

OrbitalCamera::OrbitalCamera(){}

OrbitalCamera::OrbitalCamera(Transform* _target, float _distanceTarget): mTarget(_target), mDistanceTarget(_distanceTarget)
{
    SetPosition(vec3(0,mDistanceTarget,-mDistanceTarget));
}

void OrbitalCamera::Update(const float _tickSpeed)
{
    UpdatePosition();
}

void OrbitalCamera::MoveLateral(float _move)
{
    if(!mIsActive) return;
    mAzimutAngle += _move*mMovementSpeed*Engine::Instance()->DeltaTime();
    ClampAngle(mAzimutAngle, 0, 360, true);
}

void OrbitalCamera::MoveForwardBackward(float _move)
{
    
}

void OrbitalCamera::MoveUpDown(float _move)
{
    if(!mIsActive) return;
    mElevationAngle += _move*mMovementSpeed*Engine::Instance()->DeltaTime();
    ClampAngle(mElevationAngle, -89, 89, false);
}

void OrbitalCamera::RefreshCamera()
{
    mTransform.AlignForward(mTransform.GetPosition(), mTarget->GetPosition());
}

void OrbitalCamera::UpdatePosition()
{
    const vec3 _center = mTarget->GetPosition();
    float _xPos = _center.x + cos(radians(mAzimutAngle)) * cos(radians(mElevationAngle)) * mDistanceTarget;
    float _yPos = _center.y + sin(radians(mElevationAngle)) * mDistanceTarget;
    float _zPos = _center.z + sin(radians(mAzimutAngle)) * cos(radians(mElevationAngle)) * mDistanceTarget;
    SetPosition(vec3(_xPos, _yPos, _zPos));
}

void OrbitalCamera::ClampAngle(float& _angle, const float _min, const float _max, const bool _continuity)
{
    if(_continuity)_angle = _angle >= _max ? _angle-_max : _angle < _min ? _max + _angle : _angle;
    else _angle = _angle >= _max ? _max : _angle < _min ? _min : _angle;
}