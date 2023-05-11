#include "PointLight.h"
#include "engine/Lights/LightManager/LightManager.h"


PointLight::PointLight() : GameObject()
{}

PointLight::PointLight(const vec3& _positions) : GameObject(_positions,vec3(0),vec3(1))
{}

PointLight::PointLight(const vec3& _positions, const vec3& _rotations, const vec3& _scale) : GameObject(_positions,_rotations,_scale)
{}

PointLight::~PointLight()
{}

void PointLight::Destroy()
{
    LightManager* _lightManager = LightManager::Instance();
    _lightManager->RemovePointLight(this);

    GameObject::Destroy();
}
