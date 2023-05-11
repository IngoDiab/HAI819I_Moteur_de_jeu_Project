#pragma once

#include "engine/Objects/GameObject/GameObject.h"

#include <string>
using namespace std;

class MeshComponent;
class BoxCollider;
class PhysicComponent;

class Projectile : public GameObject
{
    MeshComponent* mMeshComponent = nullptr;
    BoxCollider* mBoxCollider = nullptr;
    PhysicComponent* mPhysicComponent = nullptr;

public:
    Projectile();

public:
    void Launch(const vec3& _direction, const float _power);
};