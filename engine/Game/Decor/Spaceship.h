#pragma once

#include "engine/Objects/GameObject/GameObject.h"

#include <string>
using namespace std;

class MeshComponent;
class BoxCollider;
class PhysicComponent;
class Landscape;

class Spaceship : public GameObject
{
    MeshComponent* mMeshComponent = nullptr;
    BoxCollider* mBoxCollider = nullptr;
    PhysicComponent* mPhysicComponent = nullptr;

public:
    Spaceship();

public:
    void ModifyMaterialAttributes();
    void ClipToLandscape(Landscape* const _landscape);
};