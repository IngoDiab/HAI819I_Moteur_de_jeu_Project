#include "GameObject.h"
#include "engine/Engine/Engine.h"
#include "engine/Scenes/Scene/Scene.h"

GameObject::GameObject()
{}

GameObject::~GameObject()
{}

GameObject::GameObject(const Transform& _transform) : mTransform(_transform)
{}

GameObject::GameObject(const vec3& _positions, const vec3& _rotations, const vec3& _scale) : mTransform(_positions, _rotations, _scale)
{}

void GameObject::Update(const float _tickSpeed)
{}

Scene* GameObject::GetWorld()
{
    return Engine::Instance()->GetCurrentScene();
}

float GameObject::GetInSceneDeltaTime()
{
    return Engine::Instance()->DeltaTime()*GetWorld()->GetTickSpeed()*mTickSpeed;
}

void GameObject::RotateX(const float _rotate, const float _rotationSpeed)
{
    mTransform.RotateX(_rotate*_rotationSpeed*Engine::Instance()->DeltaTime());
}

void GameObject::RotateY(const float _rotate, const float _rotationSpeed)
{
    mTransform.RotateY(_rotate*_rotationSpeed*Engine::Instance()->DeltaTime());
}

void GameObject::RotateZ(const float _rotate, const float _rotationSpeed)
{
    mTransform.RotateZ(_rotate*_rotationSpeed*Engine::Instance()->DeltaTime());
}