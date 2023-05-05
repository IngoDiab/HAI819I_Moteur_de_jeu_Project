#pragma once
#include "engine/Objects/GameObject/GameObject.h"
#include "engine/Utils/Interfaces/IRenderable.h"
#include <string>
using namespace std;

class LandscapeMesh;
class LandscapeMaterial;
class MeshComponent;
class BoxCollider;
class PhysicComponent;

class Landscape : public GameObject, public IRenderable
{
    unsigned char* mHeightmap = nullptr;
    int mWidthImage = 0;
	int mHeightImage = 0;
    float mMaxHeight = 1;

    bool mCanRotate = false;
    float mRotateSpeed = 1;

protected:
    LandscapeMesh* mMesh = nullptr;
    map<double, LandscapeMesh*> mLODS = map<double, LandscapeMesh*>();
    LandscapeMaterial* mMaterial = nullptr;
    bool mCanBeRendered = true;

    BoxCollider* mBoxCollider = nullptr;
    PhysicComponent* mPhysicComponent = nullptr;

public:
    virtual Mesh* GetMesh(int _index = 0) override {return (Mesh*)mMesh;}
    void SetMesh(LandscapeMesh* const _mesh) {mMesh = _mesh;}

    virtual BaseMaterial* GetRendererMaterial(int _index = 0) override {return (BaseMaterial*)mMaterial;}
    LandscapeMaterial* GetMaterial() {return mMaterial;}
    void SetMaterial(LandscapeMaterial* const _material) {mMaterial = _material;}

    virtual bool CanBeRendered() const override {return mCanBeRendered;}
    void SetCanBeRendered(const bool _canBeRendered) {mCanBeRendered = _canBeRendered;}


public:
    virtual void SetScale(const vec3& _scale) override {mTransform.GetTransformData()->mLocalScale = vec3(_scale.x, 1, _scale.z);}

    bool CanRotate() const {return mCanRotate;}
    void SetCanRotate(const bool _canRotate) {mCanRotate = _canRotate;}
    void ToggleRotation(const bool _toggle) {if(_toggle) mCanRotate = !mCanRotate;}

    float GetRotationSpeed() const {return mRotateSpeed;}
    void SetRotationSpeed(const float _speed) {mRotateSpeed = _speed;}
    void ChangeSpeed(const float _change) {if(mCanRotate) mRotateSpeed += _change;}

public:
    Landscape();
    ~Landscape();

public:
    virtual void Update(const float _deltaTime) override;
    virtual void ChangeMeshByDistance(Camera* _renderingCamera, float _threshold) override;
    virtual void Render(Camera* _renderingCamera) override;
    virtual void CleanRessources() override;

public:
    void ApplyHeightmap(const string& _heightmapPath, const float _maxHeight, const float _shift);
    void ChangeResolution(const int _nbVertexWidth, const int _nbVertexLength);

    void IncreaseResolution(const bool _increase);
    void DecreaseResolution(const bool _decrease);
    
    bool InTriangle(vec3 _point, vec3 _v0, vec3 _v1, vec3 _v2, float& _u0, float& _u1, float& _u2);
    void GetProjectionOnPlane(vec3& _pointToProject, float _offset);
    vec2 UV(const vec3& _posOnPlan, const vec3& _uVector, const vec3& _vVector);
    double TexelByUV(const vec2& _uv);

private:
    void RotateLandscape();
    void CreateLandscapeMesh();
    void CreateLandscapeMaterial();
};