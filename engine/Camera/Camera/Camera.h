#pragma once

#include <glm/glm.hpp>
using namespace glm;

#include "engine/Objects/GameObject/GameObject.h"

enum class PROJECTION_TYPE
{
    PERSPECTIVE = 0,
    ORTHOGRAPHIC = 1
};

class Camera : public GameObject
{
protected:
    PROJECTION_TYPE mProjectionType = PROJECTION_TYPE::PERSPECTIVE;

    bool mIsActive = false;

    float mFOV = 45.;
    float mRatio = 4./3.;
    float mZNear = 0.1;
    float mZFar = 1000.;

public:
    Camera();
    Camera(const Transform& _transform);
    Camera(const vec3& _position, const vec3& _rotation);

public:
    vec3 GetPosition() const {return mTransform.GetPosition();}
    void SetPosition(const vec3& _position) {mTransform.SetPosition(_position);}

    vec3 GetRotation() const {return mTransform.GetRotation();}
    void SetRotation(const vec3& _rotation) {mTransform.SetRotation(_rotation);}

    vec3 GetScale() const {return mTransform.GetScale();}
    void SetScale(const vec3& _scale) {mTransform.SetScale(_scale);}

    bool IsActive() const {return mIsActive;}
    void Activate(const bool _active) {mIsActive = _active;}

public:
    virtual void RefreshCamera();

public:
    mat4 GetViewMatrix() const;
    mat4 GetProjectionMatrix() const;
};