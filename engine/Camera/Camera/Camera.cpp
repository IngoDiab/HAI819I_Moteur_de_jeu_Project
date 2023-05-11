#include "Camera.h"
#include "engine/Transform/Transform.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

Camera::Camera(){}

Camera::Camera(const Transform& _transform) : GameObject(_transform){}

Camera::Camera(const vec3& _position, const vec3& _rotation) : GameObject(_position, _rotation, vec3(1)){}

//LookAtLH & PerspectiveLH to have X = right, Y = up and Z = forward (-Z out of screen)
mat4 Camera::GetViewMatrix() const
{
    const vec3 _position = GetWorldPosition();
    const vec3 _lookAt = _position + mTransform.GetForwardVector();
    const mat4 _rotationMatrix = eulerAngleXYZ(GetWorldRotation().x, GetWorldRotation().y, GetWorldRotation().z);
    const vec4 _upV4 = _rotationMatrix * vec4(mTransform.GetUpVector(),0);
    const vec3 _up(_upV4);
    return lookAtLH(_position, _lookAt, (GetWorldRotation().x < 270 && GetWorldRotation().x > 90 ? -1.f : 1.f) * mTransform.GetUpVector());
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