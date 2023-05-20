#pragma once

#include "engine/Objects/GameObject/GameObject.h"
#include "engine/Utils/Interfaces/IRotating.h"

class MeshComponent;
class PhysicComponent;
class BoxCollider;

class Trophy : public GameObject, public IRotating
{
    MeshComponent* mMeshComponent = nullptr;
    BoxCollider* mBoxCollider = nullptr;
    PhysicComponent* mPhysicComponent = nullptr;

public:
    Trophy();
    virtual void Update(const float _tickSpeed) override;

public:
    MeshComponent* GetMeshComponent() const {return mMeshComponent;}
    BoxCollider* GetCollider() const {return mBoxCollider;}
    PhysicComponent* GetPhysicComponent() const {return mPhysicComponent;}

public:
    void RotateAroundAxis(const float _tickSpeed);
    virtual void RotateLocalAxisX(const float _rotation) override;
    virtual void RotateLocalAxisY(const float _rotation) override;
    virtual void RotateLocalAxisZ(const float _rotation) override;
};