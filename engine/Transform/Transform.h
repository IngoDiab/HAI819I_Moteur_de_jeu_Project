#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
using namespace glm;

#define TRANSFORM_VERTEX "Transform/Shader/Transform_vertex.glsl"
#define TRANSFORM_FRAG "Transform/Shader/Transform_frag.glsl"

class TransformMesh;
class TransformMaterial;
class Camera;

struct TransformData
{
    vec3 mLocalPosition = vec3(0);
    vec3 mLocalRotation = vec3(0);
    vec3 mLocalScale = vec3(1);

    vec3 mWorldPosition = vec3(0);
    vec3 mWorldRotation = vec3(0);
    vec3 mWorldScale = vec3(1);

    quat mQuaternion;

    vec3 mRightVector = vec3(1,0,0);
    vec3 mUpVector = vec3(0,1,0);
    vec3 mForwardVector = vec3(0,0,1);

    TransformData(){}
    TransformData(const vec3& _position, const vec3& _rotation, const vec3& _scale): mLocalPosition(_position), mLocalRotation(_rotation), mLocalScale(_scale){}
};

class Transform
{
    TransformMesh* mMesh = nullptr;
    TransformMaterial* mMaterial = nullptr;
    vec3 mScaleMesh = vec3(5);
    bool mDrawMeshAxis = true;

    Transform* mTransformParent = nullptr;
    TransformData mTransformData;

    mat4 mModelMatrix;
    mat4 mLocalTranslationMatrix;
    mat4 mLocalRotationMatrix;
    mat4 mLocalScaleMatrix;
    mat4 mWorldTranslationMatrix;
    mat4 mWorldRotationMatrix;
    mat4 mWorldlScaleMatrix;

    mat4 mWorldTransRotaMatrix;


public:
    TransformData GetTransformData() const {return mTransformData;}
    TransformData* GetTransformData() {return &mTransformData;}

    vec3 GetPosition() const {return mTransformData.mLocalPosition;}
    void SetPosition(const vec3& _position) {mTransformData.mLocalPosition = _position;}

    vec3 GetRotation() const {return mTransformData.mLocalRotation;}
    void SetRotation(const vec3& _rotation) {mTransformData.mLocalRotation = _rotation;}

    vec3 GetScale() const {return mTransformData.mLocalScale;}
    void SetScale(const vec3& _scale) {mTransformData.mLocalScale = _scale;}

    vec3 GetRightVector() const {return mTransformData.mRightVector;}
    vec3 GetUpVector() const {return mTransformData.mUpVector;}
    vec3 GetForwardVector() const {return mTransformData.mForwardVector;}

    mat4 GetModelMatrix(){return mModelMatrix;}

    mat4 GetWorldTransRotaMatrix(){return mWorldTransRotaMatrix;}
    mat4 GetWorldTranslationMatrix(){return mWorldTranslationMatrix;}
    mat4 GetWorldRotationMatrix(){return mWorldRotationMatrix;}
    mat4 GetWorldScaleMatrix(){return mWorldlScaleMatrix;}

    void SetParentTransform(Transform* _parent) {mTransformParent = _parent;}
    void SetDrawMeshAxis(bool _draw) {mDrawMeshAxis = _draw;}

public:
    Transform();
    Transform(const vec3& _position, const vec3& _rotation, const vec3& _scale);
    ~Transform();

public:
    void Update(const float _tickSpeed);
    void UpdateModelMatrix();

public:
    void RotateLocalAxisX(const float _offset);
    void RotateLocalAxisY(const float _offset);
    void RotateLocalAxisZ(const float _offset);
    void ApplyRotationOnLocalVectors();
    void Draw3DAxis();

public:
    void AlignForward(const vec3& _start, const vec3& _goal);

private:
    mat4 CalculateLocalTranslationMatrix();
    mat4 CalculateLocalRotationMatrix();
    mat4 CalculateLocalScaleMatrix();

    mat4 CalculateWorldTransRotaMatrix();
    mat4 CalculateWorldTranslationMatrix();
    mat4 CalculateWorldRotationMatrix();
    mat4 CalculateWorldScaleMatrix();

    void SynchronizeRightUpVectors();
    float ClampRotation(const float _offset);
};