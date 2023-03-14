#pragma once
#include "engine/Objects/GameObject/GameObject.h"

#include <string>
using namespace std;

class LandscapeMesh;
class MeshComponent;

class Landscape : public GameObject
{
    MeshComponent* mMeshComponent = nullptr;
    LandscapeMesh* mMeshLandscape = nullptr;

    string mHeightmapPath = "";
    float mMaxHeight = 1;

    bool mCanRotate = false;
    float mRotateSpeed = 1;

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

public:
    virtual void Update(const float _deltaTime) override;

public:
    void ApplyHeightmap(const string& _heightmapPath, const float _maxHeight);
    void ChangeResolution(const int _nbVertexWidth, const int _nbVertexLength);

    void IncreaseResolution(const bool _increase);
    void DecreaseResolution(const bool _decrease);

private:
    void ReApplyHeightmap(LandscapeMesh* _landscapeMesh);
    void RotateLandscape();
};