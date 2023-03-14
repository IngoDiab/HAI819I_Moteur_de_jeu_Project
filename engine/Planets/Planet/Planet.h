#pragma once

#include "engine/Objects/GameObject/GameObject.h"

class MeshComponent;

class Planet : public GameObject
{
    MeshComponent* mMeshComponent = nullptr;
    
    float mAngleRevolution = 0;
    float mRevolutionSpeed = 10;
    float mDistanceCenterRevolution = 10;

    float mAngleRotation = 0;
    float mRotationSpeed = 50;

public:
    Planet();

public:
    void SetRevolutionSpeed(const float _speed) {mRevolutionSpeed = _speed;}
    void SetDistanceCenter(const float _distance) {mDistanceCenterRevolution = _distance;}

    void SetRotationSpeed(const float _speed) {mRotationSpeed = _speed;}

public:
    MeshComponent* GetMeshComponent() const {return mMeshComponent;}

public:
    virtual void Update(const float _deltaTime) override;

private:
    void RotateAroundParent(const float _deltaTime);
    void RotateAroundAxis(const float _deltaTime);
    void ClampAngle(float& _angle, const float _min, const float _max);
};