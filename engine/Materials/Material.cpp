#include "Material.h"

#include "engine/ShaderHandlers/ShaderHandler/ShaderHandler.h"

Material::Material() : Material(CUSTOM_PBR_VERTEX, CUSTOM_PBR_FRAG)
{

}

Material::Material(const string& _vertexShader, const string& _fragShader)
{
    mShaderHandler = new ShaderHandler(_vertexShader, _fragShader);
    mShaderHandler->Initialize();
    mShader = mShaderHandler;
}

Material::~Material()
{
    for(unsigned int& _texture : mTextures)
        DeleteTexture(_texture);
}

void Material::Initialize()
{
    mColors[(int)COLOR_SLOT::AMBIENT] = vec3(.01f);
    mColors[(int)COLOR_SLOT::DIFFUSE] = vec3(1);
    mColors[(int)COLOR_SLOT::SPECULAR] = vec3(1);

    mCoeffs[(int)COEFF_SLOT::TILING] = 1;
}

void Material::UseMaterial(const mat4& _model, const mat4& _view, const mat4& _proj)
{
    BaseMaterial::UseMaterial(_model, _view, _proj);

    mShaderHandler->SendBool(mIsUsingNormalMap, mShaderHandler->GetIsUsingNormalMapHandler());

    unsigned int _nbColors = mColors.size();
    for(int _colorSlot = 0; _colorSlot<_nbColors; ++_colorSlot)
        mShaderHandler->SendVec3(mColors[_colorSlot], mShaderHandler->GetColorHandlers()[_colorSlot]);

    unsigned int _nbTextures = mTextures.size();
    for(int _textureSlot = 0; _textureSlot<_nbTextures; ++_textureSlot)
        mShaderHandler->SendTexture(GL_TEXTURE_2D, _textureSlot, mTextures[_textureSlot], mShaderHandler->GetTexturesHandlers()[_textureSlot]);

    unsigned int _nbCoeffs = mCoeffs.size();
    for(int _coeffSlot = 0; _coeffSlot<_nbCoeffs; ++_coeffSlot)
        mShaderHandler->SendFloat(mCoeffs[_coeffSlot], mShaderHandler->GetCoeffsHandlers()[_coeffSlot]);
}