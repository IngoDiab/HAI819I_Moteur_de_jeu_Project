#pragma once
#include "engine/Objects/GameObject/GameObject.h"
#include "engine/Utils/Interfaces/IRenderable.h"

#include <iostream>
using namespace std;

#define LANDSCAPE_VERTEX "Landscape/Shader/Landscape_vertex.glsl"
#define LANDSCAPE_FRAG "Landscape/Shader/Landscape_frag.glsl"

class LandscapeMesh;

class Landscape : public GameObject, public IRenderable
{
    string mHeightmapPath = "";
    float mMaxHeight = 1;

    bool mCanRotate = false;
    float mRotateSpeed = 1;

public:
    bool CanRotate() const {return mCanRotate;}
    void SetCanRotate(const bool _canRotate) {mCanRotate = _canRotate;}
    void ToggleRotation(const bool _toggle) {if(_toggle) mCanRotate = !mCanRotate;}

    float GetRotationSpeed() const {return mRotateSpeed;}
    void SetRotationSpeed(const float _speed) {mRotateSpeed = _speed;}
    void ChangeSpeed(const float _change) {if(mCanRotate) mRotateSpeed += _change;}

public:
    Landscape();
    Landscape(const int _nbVertexWidth, const int _nbVertexLength);
    Landscape(const vec3& _positions, const vec3& _rotations, const vec3& _scale);

public:
    virtual void Update(const float _deltaTime) override;
    virtual void Render(Camera* _renderingCamera) override;
    virtual void CleanRessources() override;

public:
    void ApplyHeightmap(const string& _heightmapPath, const float _maxHeight);
    void ChangeResolution(const int _nbVertexWidth, const int _nbVertexLength);

    void IncreaseResolution(const bool _increase);
    void DecreaseResolution(const bool _decrease);

private:
    void ReApplyHeightmap(LandscapeMesh* _landscapeMesh);
    void RotateLandscape();
};