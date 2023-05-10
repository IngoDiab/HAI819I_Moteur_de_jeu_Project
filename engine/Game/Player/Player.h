#pragma once

#include "engine/Objects/GameObject/GameObject.h"
#include "engine/Physic/PhysicComponent/PhysicComponent.h"
#include "engine/Physic/BoxCollider/BoxCollider.h"
#include "engine/Components/MeshComponent/MeshComponent.h"
#include "engine/Camera/Camera/Camera.h"
#include "engine/Engine//Engine.h"

using namespace glm;

class Player final : public GameObject
{
    vec3 fovRange = vec3(45,20,2); //Max, min, curve
    float maxSpeedFOV = 500;

    float mouseSensivity = 3;

    float forwardThrust = 35;
    float brakeForce = 1; float brakeMinForce = 25;
    float brakeLimit = 0.1f;
    float brakeRatio = 0.05f; float brakeCurve = 2;
public:
    Player();

private :
    MeshComponent* mMeshComponent = nullptr;
    BoxCollider* mBoxCollider = nullptr;
    PhysicComponent* mPhysicComponent = nullptr;
    Camera* mCamera = nullptr;

    void ApplyThrustForward(float force);
    void Brake(bool b);

    void TurnX(float v);
    void TurnY(float v);

    void UpdateFOV();
};
