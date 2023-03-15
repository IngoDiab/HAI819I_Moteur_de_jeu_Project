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
    if(mPathTextures == "" || mFormat == "") return;
    vector<string> _texturesCubemapPaths
    {
        mPathTextures + "right" + mFormat,
        mPathTextures + "left" + mFormat,
        mPathTextures + "top" + mFormat,
        mPathTextures + "bottom" + mFormat,
        mPathTextures + "front" + mFormat,
        mPathTextures + "back" + mFormat,
    };
    LoadCubemapTexture(0, _texturesCubemapPaths);
}

void SkyboxMaterial::UseMaterial(const int _typeTexture, const mat4& _model, const mat4& _view, const mat4& _proj)
{
    glm::mat4 _viewSkybox = glm::mat4(glm::mat3(_view)); 
    Material::UseMaterial(_typeTexture, _model, _viewSkybox, _proj);
}

void SkyboxMaterial::ChangeSkyboxTextures(const string _path, const string _format)
{
    mPathTextures = _path;
    mFormat = _format;
    Initialize();
}