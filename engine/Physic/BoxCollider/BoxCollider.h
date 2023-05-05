#pragma once
#include "engine/Physic/Collider/Collider.h"
#include <glm/glm.hpp>
using namespace glm;

class TransformMaterial;
class Cube;
class SphereCollider;

class BoxCollider : public Collider
{
private:
    TransformMaterial* mMaterial = nullptr;
    vec3 mCenterInWorld = vec3(0);

protected:
    bool mRenderAABB = true;

    Cube* mMeshOOBB = nullptr;
    Cube* mMeshAABB = nullptr;

    vec3 mCenter = vec3(0);
    vec3 mSize = vec3(1);

    mat4 mColliderMatrix = mat4(1.0f);

public:
    Cube* GetPhysicBox() const {return mMeshAABB;}
    virtual Mesh* GetMesh(int _index = 0) override {return mRenderAABB ? (Mesh*)mMeshAABB : (Mesh*)mMeshOOBB;}
    virtual BaseMaterial* GetRendererMaterial(int _index = 0) override {return (BaseMaterial*)mMaterial;}

    void SetCenter(const vec3& _center) {mCenter = _center;}
    void SetSize(const vec3& _size) {mSize = _size;}
    virtual vec3 GetCenterInWorld() const override {return mCenterInWorld;}

public:
    BoxCollider();
    virtual ~BoxCollider();

public:
    virtual void Update(const float _tickSpeed) override;
    void UpdateBox();

    CollisionData CollideCube(BoxCollider* _other);
    CollisionData CollideSphere(SphereCollider* _other);

public:
    virtual void Render(Camera* _renderingCamera) override;
    virtual void CleanRessources() override;
};