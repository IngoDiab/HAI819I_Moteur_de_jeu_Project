#include "Transform.h"

#include <glm/gtc/matrix_transform.hpp>

Transform::Transform(){}

Transform::Transform(const vec3& _position, const vec3& _rotation, const vec3& _scale) : mPosition(_position), mRotation(_rotation), mScale(_scale){}

void Transform::RotateX(const float _offset)
{
    mRotation.x = ClampRotation( mRotation.x+_offset);
}

void Transform::RotateY(const float _offset)
{
    mRotation.y = ClampRotation( mRotation.y+_offset);
}

void Transform::RotateZ(const float _offset)
{
    mRotation.z = ClampRotation( mRotation.z+_offset);
}

void Transform::ApplyRotation(const mat4& _rotationMatrix)
{
    const vec4 _forward = _rotationMatrix * vec4(vec3(0,0,1),1.0);
    mForwardVector = vec3(_forward.x, _forward.y, _forward.z);
    SynchronizeRightUpVectors();
}

void Transform::AlignForward(const vec3& _start, const vec3& _goal)
{
    mForwardVector = normalize(_goal-_start);
    SynchronizeRightUpVectors();
}

mat4 Transform::GetTranslateMatrix()
{
    return translate(mat4(1.0), mPosition);
}

mat4 Transform::GetRotationMatrix()
{
    //YAW -> PITCH -> ROLL
    return rotate(mat4(1.0), radians(mRotation.y),  vec3(0,1,0))* rotate(mat4(1.0), radians(mRotation.x), vec3(1,0,0))*rotate(mat4(1.0), radians(mRotation.z),  vec3(0,0,1));
}

mat4 Transform::GetScaleMatrix()
{
    return scale(mat4(1.0), mScale);
}

mat4 Transform::GetModelMatrix()
{
    mat4 _rotationMatrix = GetRotationMatrix();
    ApplyRotation(_rotationMatrix);
    return GetTranslateMatrix() * _rotationMatrix * GetScaleMatrix();
}

void Transform::SynchronizeRightUpVectors()
{
    const vec4 _rotatedUpOnZV4 = normalize(rotate(mat4(1.0), radians(mRotation.z),  mForwardVector)*vec4(vec3(0,1,0),1.0));
    const vec3 _rotatedUpOnZ = vec3(_rotatedUpOnZV4.x, _rotatedUpOnZV4.y, _rotatedUpOnZV4.z);
    mRightVector = normalize(cross(_rotatedUpOnZ, mForwardVector));
    mUpVector = normalize(cross(mForwardVector, mRightVector));
}

float Transform::ClampRotation(const float _rotation)
{
    return _rotation >= 360 ? _rotation-360 : _rotation < 0 ? 360 + _rotation : _rotation;
}