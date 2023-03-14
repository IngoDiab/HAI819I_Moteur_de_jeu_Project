#pragma once 

#include "engine/Camera/Camera/Camera.h"
#include "engine/Utils/Interfaces/IMoving.h"

class GameObject;

class OrbitalCamera : public Camera, public IMoving
{
    GameObject* mTarget = nullptr;
    float mDistanceTarget = 200;
    float mElevationAngle = 0;
    float mAzimutAngle = 0;

public:
    GameObject* GetTarget() const {return mTarget;}
    void SetTarget(GameObject* const _target) {mTarget = _target;}

    float GetDistanceFromTarget() const {return mDistanceTarget;}
    void SetDistanceFromTarget(const float _distance) {mDistanceTarget = _distance;}

public:
    OrbitalCamera();
    OrbitalCamera(GameObject* _target, float _distanceTarget);
    
public:
    virtual void LateUpdate(const float _tickSpeed) override;

public:
    virtual void MoveLateral(const float _move) override;
    virtual void MoveForwardBackward(const float _move) override;
    virtual void MoveUpDown(const float _move) override;

private:
    void UpdatePosition();
    void UpdateLookAtTarget();
    void ClampAngle(float& _angle, const float _min, const float _max, const bool _continuity);
};