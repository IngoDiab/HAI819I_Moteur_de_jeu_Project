#pragma once
#include "engine/Materials/BaseMaterial/BaseMaterial.h"

#include <string>
using namespace std;

class SkyboxShaderHandler;

class SkyboxMaterial : public BaseMaterial
{
protected:
    SkyboxShaderHandler* mShaderHandler = nullptr;

    unsigned int mCubemap;

public:
    SkyboxMaterial();
    SkyboxMaterial(const string& _vertexShader, const string& _fragShader);

public:
    virtual void UseMaterial(const mat4& _model, const mat4& _view, const mat4& _proj) override;

public:
    void ChangeSkyboxTextures(const string _path, const string _format);
    void LoadCubemapTexture(const vector<string>& _texturePaths);
};