#include "EarthMaterial.h"
#include "engine/ShaderHandlers/PhongShaderHandler/PhongShaderHandler.h"

EarthMaterial::EarthMaterial()
{
    PhongShaderHandler* _shaderHandler = new PhongShaderHandler(EARTH_VERTEX, EARTH_FRAG);
    _shaderHandler->Initialize();
    SetShader(_shaderHandler);
}

EarthMaterial::EarthMaterial(const string& _vertexShader, const string& _fragShader)
{
    PhongShaderHandler* _shaderHandler = new PhongShaderHandler(_vertexShader, _fragShader);
    _shaderHandler->Initialize();
    SetShader(_shaderHandler);
}

void EarthMaterial::Initialize()
{
    LoadTexture(0, "Textures/2D/earth.jpg");
}