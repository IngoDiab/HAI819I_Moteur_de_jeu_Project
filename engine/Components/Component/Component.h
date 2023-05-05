#pragma once

#include "engine/Transform/Transform.h"
#include "engine/Utils/Interfaces/ITickable.h"

class GameObject;

class Component : public ITickable
{
protected:
    bool mIsDirty = true;
    GameObject* mOwner = nullptr;
    Transform mTransform;

public:
    bool IsDirty() const {return mIsDirty;}
    GameObject* GetOwner() const {return mOwner;}

    Transform* GetTransformInstance() {return &mTransform;}
    TransformData GetTransform() const {return mTransform.GetTransformData();}

    vec3 GetWorldPosition() const {return GetTransform().mWorldPosition;}
    vec3 GetLocalPosition() const {return GetTransform().mLocalPosition;}
    void SetPosition(const vec3& _position) {mTransform.GetTransformData()->mLocalPosition = _position;}

    vec3 GetWorldRotation() const {return GetTransform().mWorldRotation;}
    vec3 GetLocalRotation() const {return GetTransform().mLocalRotation;}
    void SetRotation(const vec3& _rotation) {mTransform.GetTransformData()->mLocalRotation = _rotation;}

    vec3 GetWorldScale() const {return GetTransform().mWorldScale;}
    vec3 GetLocalScale() const {return GetTransform().mLocalScale;}
    void SetScale(const vec3& _scale) {mTransform.GetTransformData()->mLocalScale = _scale;}

public:
    virtual void PostConstructor();

public:
    virtual void Update(const float _tickSpeed);
    virtual void LateUpdate(const float _tickSpeed);

public:
    void UpdateModelMatrix();    
    void Draw3DAxis();
    void SetOwner(GameObject* _owner);
};