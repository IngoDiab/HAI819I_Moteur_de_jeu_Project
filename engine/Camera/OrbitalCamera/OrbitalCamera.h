#pragma once 

#include "engine/Camera/Camera/Camera.h"
#include "engine/Utils/Interfaces/IMoving.h"

class Transform;

class OrbitalCamera : public Camera, public IMoving
{
    Transform* mTarget = nullptr;
    float mDistanceTarget = 200;
    float mElevationAngle = 45;
    float mAzimutAngle = 0;

public:
    Transform* GetTarget() const {return mTarget;}
    void SetTarget(Transform* const _target) {mTarget = _target;}

    float GetDistanceFromTarget() const {return mDistanceTarget;}
    void SetDistanceFromTarget(const float _distance) {mDistanceTarget = _distance;}

public:
    OrbitalCamera();
    OrbitalCamera(Transform* _target, float _distanceTarget);
    
public:
    virtual void Update(const float _tickSpeed) override;

public:
    virtual void MoveLateral(const float _move) override;
    virtual void MoveForwardBackward(const float _move) override;
    virtual void MoveUpDown(const float _move) override;

public:
    virtual void RefreshCamera() override;

private:
    void UpdatePosition();
    void ClampAngle(float& _angle, const float _min, const float _max, const bool _continuity);
};