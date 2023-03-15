#include "PlanetMaterial.h"
#include "engine/ShaderHandlers/PhongShaderHandler/PhongShaderHandler.h"

PlanetMaterial::PlanetMaterial()
{
    PhongShaderHandler* _shaderHandler = new PhongShaderHandler(SUN_VERTEX, SUN_FRAG);
    _shaderHandler->Initialize();
    SetShader(_shaderHandler);
}

PlanetMaterial::PlanetMaterial(const string& _vertexShader, const string& _fragShader)
{
    PhongShaderHandler* _shaderHandler = new PhongShaderHandler(_vertexShader, _fragShader);
    _shaderHandler->Initialize();
    SetShader(_shaderHandler);
}

void PlanetMaterial::Initialize()
{

}