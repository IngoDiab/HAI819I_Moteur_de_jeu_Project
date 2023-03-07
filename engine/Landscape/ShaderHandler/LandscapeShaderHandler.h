#pragma once
#include "engine/ShaderHandlers/ShaderHandler/ShaderHandler.h"

class LandscapeShaderHandler : public ShaderHandler
{
public:
    LandscapeShaderHandler(const string& _vertexShader, const string& _fragShader);

public:
    virtual void Initialize() override;
};
