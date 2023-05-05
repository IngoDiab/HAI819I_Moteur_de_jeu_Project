#include "BaseMaterial.h"
#include "engine/ShaderHandlers/BaseShaderHandler/BaseShaderHandler.h"

void BaseMaterial::DeleteTexture(unsigned int& _texture)
{
    if(!glIsTexture(_texture)) return;
    glDeleteTextures(1, &_texture);
}

void BaseMaterial::UseMaterial(const mat4& _model, const mat4& _view, const mat4& _proj)
{
    mShader->SendMVP(_model, _view, _proj);
    mShader->SendLights();
}

void BaseMaterial::LoadTexture(unsigned int& _textureSlot, const string& _texturePath)
{
    if(_texturePath == "") return;
    DeleteTexture(_textureSlot);
    _textureSlot = loadTexture2DFromFilePath(_texturePath);
}