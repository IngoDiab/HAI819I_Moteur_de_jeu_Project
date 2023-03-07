#pragma once
#include "engine/ShaderHandlers/ShaderHandler/ShaderHandler.h"

class SkyboxShaderHandler : public ShaderHandler
{
public:
    SkyboxShaderHandler(const string& _vertexShader, const string& _fragShader);

public:
    virtual void Initialize() override;
};
