#include "MoonMaterial.h"
#include "engine/ShaderHandlers/PhongShaderHandler/PhongShaderHandler.h"

MoonMaterial::MoonMaterial()
{
    PhongShaderHandler* _shaderHandler = new PhongShaderHandler(MOON_VERTEX, MOON_FRAG);
    _shaderHandler->Initialize();
    SetShader(_shaderHandler);
}

MoonMaterial::MoonMaterial(const string& _vertexShader, const string& _fragShader)
{
    PhongShaderHandler* _shaderHandler = new PhongShaderHandler(_vertexShader, _fragShader);
    _shaderHandler->Initialize();
    SetShader(_shaderHandler);
}

void MoonMaterial::Initialize()
{
    LoadTexture(0, "Textures/2D/moon.jpg");
}