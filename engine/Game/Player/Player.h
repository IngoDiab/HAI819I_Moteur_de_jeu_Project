#pragma once

#include "engine/Objects/GameObject/GameObject.h"
#include "engine/Physic/PhysicComponent/PhysicComponent.h"
#include "engine/Physic/BoxCollider/BoxCollider.h"
#include "engine/Components/MeshComponent/MeshComponent.h"
#include "engine/Camera/Camera/Camera.h"
#include "engine/Engine//Engine.h"

class Player final : public GameObject
{
public:
    Player();

private :
    MeshComponent* mMeshComponent = nullptr;
    BoxCollider* mBoxCollider = nullptr;
    PhysicComponent* mPhysicComponent = nullptr;
    Camera* mCamera = nullptr;

    float forwardThrust;

    void ApplyThrustForward(float force);
};
