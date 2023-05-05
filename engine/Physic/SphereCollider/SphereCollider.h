#pragma once
#include "engine/Physic/Collider/Collider.h"
#include "engine/Physic/CollisionData/CollisionData.h"
#include <glm/glm.hpp>
using namespace glm;

class TransformMaterial;
class Sphere;
class BoxCollider;

class SphereCollider : public Collider
{
private:
    TransformMaterial* mMaterial = nullptr;
    vec3 mCenterInWorld = vec3(0);

protected:
    Sphere* mMesh = nullptr;

    vec3 mCenter = vec3(0);
    float mRadius = 1;
    bool mIsTrigger = false;

    mat4 mColliderMatrix = mat4(1.0f);

public:
    virtual Mesh* GetMesh(int _index = 0) override {return (Mesh*)mMesh;}
    virtual BaseMaterial* GetRendererMaterial(int _index = 0) override {return (BaseMaterial*)mMaterial;}

    void SetCenter(const vec3& _center) {mCenter = _center;}
    void SetRadius(const float _radius) {mRadius = _radius;}

    virtual vec3 GetCenterInWorld() const override {return mCenterInWorld;}
    float GetRadius() const {return mRadius;}

public:
    SphereCollider();
    virtual ~SphereCollider();

public:
    virtual void Update(const float _tickSpeed) override;
    void UpdateSphere();

    CollisionData CollideCube(BoxCollider* _other);
    CollisionData CollideSphere(SphereCollider* _other);

public:
    virtual void Render(Camera* _renderingCamera) override;
    virtual void CleanRessources() override;
};