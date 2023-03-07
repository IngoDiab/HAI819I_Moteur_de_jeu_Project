#pragma once

#include <glm/glm.hpp>
using namespace glm;

class Transform
{
    vec3 mPosition = vec3(0);
    vec3 mRotation = vec3(0);
    vec3 mScale = vec3(1);

    vec3 mRightVector = vec3(1,0,0);
    vec3 mUpVector = vec3(0,1,0);
    vec3 mForwardVector = vec3(0,0,1);

public:
    vec3 GetPosition() const {return mPosition;}
    void SetPosition(const vec3& _position) {mPosition = _position;}

    vec3 GetRotation() const {return mRotation;}
    void SetRotation(const vec3& _rotation) {mRotation = _rotation;}

    vec3 GetScale() const {return mScale;}
    void SetScale(const vec3& _scale) {mScale = _scale;}

    vec3 GetRightVector() const {return mRightVector;}
    vec3 GetUpVector() const {return mUpVector;}
    vec3 GetForwardVector() const {return mForwardVector;}

public:
    Transform();
    Transform(const vec3& _position, const vec3& _rotation, const vec3& _scale);

public:
    void RotateX(const float _offset);
    void RotateY(const float _offset);
    void RotateZ(const float _offset);
    void ApplyRotation(const mat4& _rotationMatrix);

public:
    void AlignForward(const vec3& _start, const vec3& _goal);
    mat4 GetTranslateMatrix();
    mat4 GetRotationMatrix();
    mat4 GetScaleMatrix();
    mat4 GetModelMatrix();

private:
    void SynchronizeRightUpVectors();
    float ClampRotation(const float _offset);
};