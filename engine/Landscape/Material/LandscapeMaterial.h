#pragma once

#include "engine/Materials/Material.h"

#include <string>
using namespace std;

class LandscapeMaterial : public Material
{
    float mHeightGrassRock = 50;
    float mHeightRockSnow = 80;
    float mTransitionThreshold = 10;
    int mTiling = 20;

public:
    LandscapeMaterial();
    LandscapeMaterial(const string& _vertexShader, const string& _fragShader);

public:
    virtual void Initialize() override;

    virtual void UseMaterial(const int _typeTexture, const mat4& _model, const mat4& _view, const mat4& _proj) override;
};