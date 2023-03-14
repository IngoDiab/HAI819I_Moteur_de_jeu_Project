#include "SunMaterial.h"
#include "engine/ShaderHandlers/PhongShaderHandler/PhongShaderHandler.h"

SunMaterial::SunMaterial()
{
    PhongShaderHandler* _shaderHandler = new PhongShaderHandler(SUN_VERTEX, SUN_FRAG);
    _shaderHandler->Initialize();
    SetShader(_shaderHandler);
}

SunMaterial::SunMaterial(const string& _vertexShader, const string& _fragShader)
{
    PhongShaderHandler* _shaderHandler = new PhongShaderHandler(_vertexShader, _fragShader);
    _shaderHandler->Initialize();
    SetShader(_shaderHandler);
}

void SunMaterial::Initialize()
{
    LoadTexture(0, "Textures/2D/sun.jpg");
}