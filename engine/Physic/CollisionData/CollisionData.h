#pragma once

#include <glm/glm.hpp>
using namespace glm;

class PhysicComponent;

struct CollisionData
{
    bool mAreColliding = false;
    PhysicComponent* mMainComponent = nullptr;
    PhysicComponent* mOtherComponent = nullptr;
    vec3 mImpactPosition = vec3(0);
    vec3 mImpactNormale = vec3(0);
    float mAmountInCollision = 0;
};
