#include "SkyboxMaterial.h"
#include "engine/Skyboxes/ShaderHandler/SkyboxShaderHandler.h"
#include <iostream>
using namespace std;

SkyboxMaterial::SkyboxMaterial(){}

SkyboxMaterial::SkyboxMaterial(const string& _vertexShader, const string& _fragShader)
{
    SkyboxShaderHandler* _shaderHandler = new SkyboxShaderHandler(_vertexShader, _fragShader);
    _shaderHandler->Initialize();
    SetShader(_shaderHandler);
}

void SkyboxMaterial::Initialize()
{
    const string _path = "Textures/Skybox/Base/";
    const string _format = ".jpg";
    vector<string> _texturesCubemapPaths
    {
        _path + "right" + _format,
        _path + "left" + _format,
        _path + "top" + _format,
        _path + "bottom" + _format,
        _path + "front" + _format,
        _path + "back" + _format,
    };
    LoadCubemapTexture(0, _texturesCubemapPaths);
}

void SkyboxMaterial::UseMaterial(const int _typeTexture, const mat4& _model, const mat4& _view, const mat4& _proj)
{
    glm::mat4 _viewSkybox = glm::mat4(glm::mat3(_view)); 
    Material::UseMaterial(_typeTexture, _model, _viewSkybox, _proj);
}