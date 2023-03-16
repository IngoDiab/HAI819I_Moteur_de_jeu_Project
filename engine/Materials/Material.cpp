#include "Material.h"
#include "engine/ShaderHandlers/ShaderHandler/ShaderHandler.h"

Material::~Material()
{
    for(unsigned int& _texture : mTextures)
        DeleteTexture(_texture);
}

void Material::DeleteTexture(unsigned int& _texture)
{
    if(!glIsTexture(_texture)) return;
    glDeleteTextures(1, &_texture);
}

void Material::UseMaterial(const int _typeTexture, const mat4& _model, const mat4& _view, const mat4& _proj)
{
    mShader->SendLights();
    mShader->SendMVP(_model, _view, _proj);
    for(int _textureSlot = 0; _textureSlot<16; ++_textureSlot)
        mShader->SendTexture(_typeTexture, _textureSlot, mTextures[_textureSlot]);
}

void Material::LoadTexture(const int _textureSlot, const string& _texturePath)
{
    DeleteTexture(mTextures[_textureSlot]);
    mTextures[_textureSlot] = loadTexture2DFromFilePath(_texturePath);
}

void Material::LoadCubemapTexture(const int _textureSlot, const vector<string>& _texturePaths)
{
    DeleteTexture(mTextures[_textureSlot]);
    mTextures[_textureSlot] = loadTextureCubeMap2DFromFilePath(_texturePaths);
}