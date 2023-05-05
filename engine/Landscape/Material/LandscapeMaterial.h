#pragma once

#include "engine/Materials/BaseMaterial/BaseMaterial.h"

#include <string>
using namespace std;

class LandscapeShaderHandler;

class LandscapeMaterial final : public BaseMaterial
{
protected:
    LandscapeShaderHandler* mShaderHandler = nullptr;

    unsigned int mHeightmap;
    float mHeight = 1;
    float mShift = 1;

    vector<unsigned int> mLayers = vector<unsigned int>(15);
    vector<float> mHeightsTransition = vector<float>(14);
    float mTransitionThreshold = 10;
    
    int mTiling = 20;

public:
    void SetHeightmap(const string& _map, const float _height){LoadTexture(mHeightmap, _map); mHeight=_height;}
    void SetHeight(const float _height){mHeight=_height;}
    float GetShift() const {return mShift;}
    void SetShift(const float _shift){mShift=_shift;}
    void AddLayer(unsigned int _slot, const string& _pathTexture){DeleteTexture(mLayers[_slot]), LoadTexture(mLayers[_slot], _pathTexture);}
    void AddTransition(unsigned int _slot, float _transition){mHeightsTransition[_slot] = _transition;}
    void SetTreshold(float _threshold){mTransitionThreshold = _threshold;}
    void SetTiling(int _tiling){mTiling = _tiling;}

public:
    LandscapeMaterial();
    LandscapeMaterial(const string& _vertexShader, const string& _fragShader);

public:
    virtual void UseMaterial(const mat4& _model, const mat4& _view, const mat4& _proj) override;

public:
    void SendHeightmap();
    void SendLayers();
    void SendTransition();
};