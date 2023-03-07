#pragma once 

#include "engine/Objects/Object/Object.h"
#include "engine/Transform/Transform.h"
#include "engine/Utils/Interfaces/ITickable.h"

class Camera;
class Scene;

class GameObject : public Object, public ITickable
{
protected:
    Transform mTransform;
    //GameObject* mParent = nullptr;

public :
    GameObject();
    virtual ~GameObject();
    GameObject(const Transform& _transform);
    GameObject(const vec3& _positions, const vec3& _rotations, const vec3& _scale);

public:
    Transform* GetTransform() {return &mTransform;}

public:
    virtual void Update(const float _tickSpeed) override;
    Scene* GetWorld();
    float GetInSceneDeltaTime();

public:
    virtual void RotateX(const float _rotate, const float _rotationSpeed);
    virtual void RotateY(const float _rotate, const float _rotationSpeed);
    virtual void RotateZ(const float _rotate, const float _rotationSpeed);
};