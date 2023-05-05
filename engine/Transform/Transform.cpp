#include "Transform.h"
#include <glm/gtc/matrix_transform.hpp>
#include "engine/Transform/Mesh/TransformMesh.h"
#include "engine/Transform/Material/TransformMaterial.h"
#include "engine/ShaderHandlers/ShaderHandler/ShaderHandler.h"
#include "engine/Engine/Engine.h"

Transform::Transform()
{
    mMesh = new TransformMesh();
    mMaterial = new TransformMaterial(TRANSFORM_VERTEX, TRANSFORM_FRAG);
}

Transform::Transform(const vec3& _position, const vec3& _rotation, const vec3& _scale) : mTransformData(TransformData(_position, _rotation, _scale))
{
    mMesh = new TransformMesh();
    mMaterial = new TransformMaterial(TRANSFORM_VERTEX, TRANSFORM_FRAG);
}

Transform::~Transform()
{
    delete mMesh;
    delete mMaterial;
}

void Transform::Update(const float _tickSpeed)
{
    if(!mTransformParent)
    {
        mTransformData.mWorldPosition = mTransformData.mLocalPosition;
        mTransformData.mWorldRotation = mTransformData.mLocalRotation;
        mTransformData.mWorldScale = mTransformData.mLocalScale;
    }
    else
    {
        TransformData _parentData = *mTransformParent->GetTransformData();
        mTransformData.mWorldPosition = mTransformData.mLocalPosition + _parentData.mWorldPosition;
        mTransformData.mWorldRotation = mTransformData.mLocalRotation + _parentData.mWorldRotation;
        mTransformData.mWorldScale = mTransformData.mLocalScale * _parentData.mWorldScale;
    }
}

void Transform::UpdateModelMatrix()
{
    CalculateLocalTranslationMatrix();
    CalculateLocalRotationMatrix();
    CalculateLocalScaleMatrix();

    CalculateWorldTranslationMatrix();
    CalculateWorldRotationMatrix();
    CalculateWorldScaleMatrix();
    CalculateWorldTransRotaMatrix();

    ApplyRotationOnLocalVectors();

    mModelMatrix = GetWorldTransRotaMatrix() * GetWorldScaleMatrix();
}

void Transform::RotateLocalAxisX(const float _offset)
{
    mTransformData.mLocalRotation.x = ClampRotation( mTransformData.mLocalRotation.x+_offset);
}

void Transform::RotateLocalAxisY(const float _offset)
{
    mTransformData.mLocalRotation.y = ClampRotation( mTransformData.mLocalRotation.y+_offset);
}

void Transform::RotateLocalAxisZ(const float _offset)
{
    mTransformData.mLocalRotation.z = ClampRotation( mTransformData.mLocalRotation.z+_offset);
}

void Transform::ApplyRotationOnLocalVectors()
{
    const vec4 _forward = GetWorldRotationMatrix() * vec4(vec3(0,0,1),1.0);
    mTransformData.mForwardVector = vec3(_forward.x, _forward.y, _forward.z);
    SynchronizeRightUpVectors();
}

void Transform::Draw3DAxis()
{
    if(!mDrawMeshAxis) return;
    Camera* _renderingCamera = Engine::Instance()->GetViewportCamera();
    //Calculate VP
    const mat4& _viewMatrix = _renderingCamera->GetViewMatrix();
    const mat4& _projMatrix = _renderingCamera->GetProjectionMatrix();
    //Use Material
    glUseProgram(mMaterial->GetShader()->GetShaderHandler());
    const mat4 _transformModel = GetWorldTransRotaMatrix() * scale(mat4(1.0), mScaleMesh);
    mMaterial->UseMaterial(_transformModel, _viewMatrix, _projMatrix);

    //Draw
    mMesh->DrawMesh();
}

void Transform::AlignForward(const vec3& _start, const vec3& _goal)
{
    mTransformData.mForwardVector = normalize(_goal-_start);
    SynchronizeRightUpVectors();
}

mat4 Transform::CalculateLocalTranslationMatrix()
{
    return mLocalTranslationMatrix = translate(mat4(1.0), mTransformData.mLocalPosition);
}

mat4 Transform::CalculateLocalRotationMatrix()
{
    //YAW -> PITCH -> ROLL
    return mLocalRotationMatrix = rotate(mat4(1.0), radians(mTransformData.mLocalRotation.y),  vec3(0,1,0))* rotate(mat4(1.0), radians(mTransformData.mLocalRotation.x), vec3(1,0,0))*rotate(mat4(1.0), radians(mTransformData.mLocalRotation.z),  vec3(0,0,1));
}

mat4 Transform::CalculateLocalScaleMatrix()
{
    return mLocalScaleMatrix = scale(mat4(1.0), mTransformData.mLocalScale);
}

mat4 Transform::CalculateWorldTransRotaMatrix()
{
    return mWorldTransRotaMatrix = (mTransformParent ? mTransformParent->GetWorldTransRotaMatrix() : mat4(1.0f))* mLocalTranslationMatrix * mLocalRotationMatrix;
}

mat4 Transform::CalculateWorldTranslationMatrix()
{
    return mWorldTranslationMatrix = translate(mat4(1.0), mTransformData.mWorldPosition);
}

mat4 Transform::CalculateWorldRotationMatrix()
{
    //YAW -> PITCH -> ROLL
    return mWorldRotationMatrix = rotate(mat4(1.0), radians(mTransformData.mWorldRotation.y),  vec3(0,1,0))* rotate(mat4(1.0), radians(mTransformData.mWorldRotation.x), vec3(1,0,0))*rotate(mat4(1.0), radians(mTransformData.mWorldRotation.z),  vec3(0,0,1));
}

mat4 Transform::CalculateWorldScaleMatrix()
{
    return mWorldlScaleMatrix = scale(mat4(1.0), mTransformData.mWorldScale);
}

void Transform::SynchronizeRightUpVectors()
{
    const vec4 _rotatedUpOnZV4 = normalize(rotate(mat4(1.0), radians(mTransformData.mWorldRotation.z),  mTransformData.mForwardVector)*vec4(vec3(0,1,0),1.0));
    const vec3 _rotatedUpOnZ = vec3(_rotatedUpOnZV4.x, _rotatedUpOnZV4.y, _rotatedUpOnZV4.z);
    mTransformData.mRightVector = normalize(cross(_rotatedUpOnZ, mTransformData.mForwardVector));
    mTransformData.mUpVector = normalize(cross(mTransformData.mForwardVector, mTransformData.mRightVector));
}

float Transform::ClampRotation(const float _rotation)
{
    return _rotation >= 360 ? _rotation-360 : _rotation < 0 ? 360 + _rotation : _rotation;
}