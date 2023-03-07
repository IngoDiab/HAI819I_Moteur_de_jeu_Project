#include "Camera.h"
#include "engine/Transform/Transform.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(){}

Camera::Camera(const Transform& _transform) : GameObject(_transform){}

Camera::Camera(const vec3& _position, const vec3& _rotation) : GameObject(_position, _rotation, vec3(1)){}

void Camera::RefreshCamera()
{
    const mat4 _rotationMatrix = mTransform.GetRotationMatrix();
    mTransform.ApplyRotation(_rotationMatrix);
}

//LookAtLH & PerspectiveLH to have X = right, Y = up and Z = forward (-Z out of screen)
mat4 Camera::GetViewMatrix() const
{
    const vec3 _position = mTransform.GetPosition();
    const vec3 _lookAt = _position + mTransform.GetForwardVector();
    return lookAtLH(_position, _lookAt, mTransform.GetUpVector());
}

mat4 Camera::GetProjectionMatrix() const
{
    switch (mProjectionType)
    {
    case PROJECTION_TYPE::PERSPECTIVE:
        return perspectiveLH(radians(mFOV), mRatio, mZNear, mZFar);
        break;

    case PROJECTION_TYPE::ORTHOGRAPHIC:
        //TODO implement ortho projection
        return mat4(1.0);
        break;
    
    default:
        return mat4(1.0);
        break;
    }
}