#pragma once
#include "engine/ShaderHandlers/ShaderHandler/ShaderHandler.h"

class PhongShaderHandler : public ShaderHandler
{
public:
    PhongShaderHandler(const string& _vertexShader, const string& _fragShader);

public:
    virtual void Initialize() override;
};
