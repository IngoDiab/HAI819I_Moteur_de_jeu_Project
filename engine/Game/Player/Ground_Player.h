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

public:
    Ground_Player();

private:
    Camera* CreatePlayerCamera();

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

public:
    void ClipToLandscape(Landscape* const _landscape);
};