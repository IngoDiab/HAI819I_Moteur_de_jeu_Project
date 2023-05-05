#pragma once
#include "engine/ShaderHandlers/BaseShaderHandler/BaseShaderHandler.h"

class SkyboxShaderHandler final : public BaseShaderHandler
{
public:
    int mCubemapHandler;

public:
    int GetCubemapHandler() const {return mCubemapHandler;}

public:
    SkyboxShaderHandler(const string& _vertexShader, const string& _fragShader);

public:
    virtual void Initialize() override;
};
