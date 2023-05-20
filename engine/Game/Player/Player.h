#pragma once

#include "engine/Objects/GameObject/GameObject.h"

class PhysicComponent;
class BoxCollider;
class MeshComponent;
class Camera;

using namespace glm;

class Player final : public GameObject
{
    vec3 fovRange = vec3(45,20,2); //Max, min, curve
    float maxSpeedFOV = 500;

    float mouseSensivity = 3;

    float forwardThrust = 75;
    float brakeForce = 10; float brakeMinForce = 25;
    float brakeLimit = 0.1f;
    float brakeRatio = 0.05f; float brakeCurve = 2;

    float mShotPower = 2000;
public:
    Player();

private :
    GameObject* mLeftCanon = nullptr;
    GameObject* mRightCanon = nullptr;
    MeshComponent* mMeshComponent = nullptr;
    BoxCollider* mBoxCollider = nullptr;
    PhysicComponent* mPhysicComponent = nullptr;
    Camera* mCamera = nullptr;

    void InitializeCanons();
    void Shoot(bool _shootPressed);

    void ApplyThrustForward(float force);
    void Brake(bool b);

    void TurnX(float v);
    void TurnY(float v);

    void UpdateFOV();
};
