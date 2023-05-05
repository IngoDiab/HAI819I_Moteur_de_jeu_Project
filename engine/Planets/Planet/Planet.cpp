#include "Planet.h"

#include "engine/Components/MeshComponent/MeshComponent.h"
#include "engine/Meshs/Sphere/Sphere.h"

Planet::Planet()
{
    mMeshComponent = AddComponent<MeshComponent>();
    mMeshComponent->CreateMesh<Sphere>();
    mMeshComponent->CreateMaterial<Material>(PHONG_VERTEX, PHONG_FRAG);
}

void Planet::Update(const float _deltaTime)
{
    GameObject::Update(_deltaTime);
    RotateAroundParent(_deltaTime);
    RotateAroundAxis(_deltaTime);
}

void Planet::RotateAroundParent(const float _deltaTime)
{
    if(!mParent) return;
    mAngleRevolution += _deltaTime*mRevolutionSpeed;
    ClampAngle(mAngleRevolution, 0, 360);
    float _xPos = cos(radians(mAngleRevolution)) * mDistanceCenterRevolution;
    float _zPos = sin(radians(mAngleRevolution)) * mDistanceCenterRevolution;
    SetPosition(vec3(_xPos, 0, _zPos));
}

void Planet::RotateAroundAxis(const float _deltaTime)
{
    if(!mParent) return;
    mMeshComponent->GetTransformInstance()->RotateLocalAxisY(mRotationSpeed*_deltaTime);
}

void Planet::ClampAngle(float& _angle, const float _min, const float _max)
{
    _angle = _angle >= _max ? _angle-_max : _angle < _min ? _max + _angle : _angle;
}