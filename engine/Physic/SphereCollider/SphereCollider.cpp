#include "SphereCollider.h"
#include "engine/Meshs/Sphere/Sphere.h"
#include "engine/Transform/Material/TransformMaterial.h"
#include "engine/Camera/Camera/Camera.h"
#include "engine/ShaderHandlers/BaseShaderHandler/BaseShaderHandler.h"
#include "engine/FilesPath/FilesPath.h"
#include "engine/Engine/Engine.h"
#include "engine/Windows/Window.h"
#include "engine/Physic/SphereCollider/SphereCollider.h"
#include <glm/gtc/matrix_transform.hpp>
#include <limits>

SphereCollider::SphereCollider()
{
    mMesh = new Sphere(true, false, true, false);
    mMaterial = new TransformMaterial(COLLIDER_VERTEX, COLLIDER_FRAG);
}

SphereCollider::~SphereCollider()
{
    CleanRessources();
}

void SphereCollider::Update(const float _tickSpeed)
{
    Collider::Update(_tickSpeed);
    UpdateSphere();
}

void SphereCollider::UpdateSphere()
{   
    mColliderMatrix = mOwner->GetTransformInstance()->GetModelMatrix() * translate(mat4(1.0), mCenter) * scale(mat4(1.0), vec3(mRadius));
    vec4 _centerV4 = mColliderMatrix*vec4(mCenter,1);
    mCenterInWorld = vec3(_centerV4.x, _centerV4.y, _centerV4.z);
}

CollisionData SphereCollider::CollideCube(BoxCollider* _other)
{
   return CollisionData();
}

CollisionData SphereCollider::CollideSphere(SphereCollider* _other)
{
    CollisionData _data = CollisionData();

    vec3 _alignementSphere = mCenterInWorld - _other->GetCenterInWorld();

    float _distance = length(_alignementSphere);
    bool _colliding = _distance < _other->GetRadius() + mRadius;

    if(!_colliding) return _data;
    _data.mAreColliding = true;
    _data.mImpactNormale = normalize(_alignementSphere);
    return _data;
}

void SphereCollider::Render(Camera* _renderingCamera)
{
    //Calculate MVP
    const mat4& _modelMatrix = mColliderMatrix;
    const mat4& _viewMatrix = _renderingCamera->GetViewMatrix();
    const mat4& _projMatrix = _renderingCamera->GetProjectionMatrix();

    //Use Material
    glUseProgram(mMaterial->GetShader()->GetShaderHandler());
    mMaterial->UseMaterial(_modelMatrix, _viewMatrix, _projMatrix);

    Engine::Instance()->GetWindow()->PolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    //Draw
    mMesh->DrawMesh();

    Engine::Instance()->GetWindow()->PolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void SphereCollider::CleanRessources()
{
    delete mMesh;
    delete mMaterial;
}