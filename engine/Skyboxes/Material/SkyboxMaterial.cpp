#include "SkyboxMaterial.h"
#include "engine/Skyboxes/ShaderHandler/SkyboxShaderHandler.h"

SkyboxMaterial::SkyboxMaterial(){}

SkyboxMaterial::SkyboxMaterial(const string& _vertexShader, const string& _fragShader)
{
    mShaderHandler = new SkyboxShaderHandler(_vertexShader, _fragShader);
    mShaderHandler->Initialize();
    mShader = mShaderHandler;
}

void SkyboxMaterial::UseMaterial(const mat4& _model, const mat4& _view, const mat4& _proj)
{
    glm::mat4 _viewSkybox = glm::mat4(glm::mat3(_view)); 
    BaseMaterial::UseMaterial(_model, _viewSkybox, _proj);

    mShaderHandler->SendTexture(GL_TEXTURE_CUBE_MAP, 0, mCubemap, mShaderHandler->GetCubemapHandler());
}

void SkyboxMaterial::ChangeSkyboxTextures(const string _path, const string _format)
{
    if(_path == "" || _format == "") return;
    vector<string> _texturesCubemapPaths
    {
        _path + "right" + _format,
        _path + "left" + _format,
        _path + "top" + _format,
        _path + "bottom" + _format,
        _path + "front" + _format,
        _path + "back" + _format,
    };
    LoadCubemapTexture(_texturesCubemapPaths);
}

void SkyboxMaterial::LoadCubemapTexture(const vector<string>& _texturePaths)
{
    DeleteTexture(mCubemap);
    mCubemap = loadTextureCubeMap2DFromFilePath(_texturePaths);
}