#include "DirectionalLight.h"
#include "engine/Lights/LightManager/LightManager.h"

DirectionalLight::DirectionalLight() : GameObject()
{}

DirectionalLight::DirectionalLight(const vec3& _color, const vec3& _direction) : mColor(_color), mDirection(_direction)
{}

DirectionalLight::~DirectionalLight()
{}

void DirectionalLight::Destroy()
{
    LightManager* _lightManager = LightManager::Instance();
    _lightManager->RemoveDirectionalLight(this);
    
    GameObject::Destroy();
}