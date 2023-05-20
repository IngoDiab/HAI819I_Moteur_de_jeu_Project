#pragma once

#include "engine/Objects/GameObject/GameObject.h"
#include "engine/Utils/Interfaces/IMoving.h"
#include "engine/Utils/Interfaces/IRotating.h"

#include <string>
using namespace std;

class MeshComponent;
class BoxCollider;
class PhysicComponent;
class Landscape;
class Camera;

class Ground_Player : public GameObject, public IMoving, public IRotating
{
    MeshComponent* mMeshComponent = nullptr;
    BoxCollider* mBoxCollider = nullptr;
    PhysicComponent* mPhysicComponent = nullptr;

    Camera* mPlayerCamera = nullptr;

    float mHeightJump = 50;

    float mTargetSpeed = 50;

    float mRunSpeed = 150;
    float mWalkSpeed = 50;
    float mAcceleration = 1;
    float mDeceleration = 10;

public:
    Ground_Player();
    virtual void Update(const float _tickSpeed) override;

private:
    Camera* CreatePlayerCamera();
    void UpdatePlayerSpeed(const float _tickSpeed);

public:
    virtual void MoveLateral(const float _move) override;
    virtual void MoveForwardBackward(const float _move) override;
    virtual void MoveUpDown(const float _move) override;

    void LateralVelocity(const float _move);
    void ForwardBackwardVelocity(const float _move);
    void Jump(const bool _move);

    virtual void RotateLocalAxisX(float _rotation) override;
    virtual void RotateLocalAxisY(float _rotation) override;
    virtual void RotateLocalAxisZ(float _rotation) override;

    void RunSpeed(const bool _pressed);

public:
    void ClipToLandscape(Landscape* const _landscape);
};