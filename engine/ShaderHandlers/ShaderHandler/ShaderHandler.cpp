#include "ShaderHandler.h"
#include <GL/glew.h>
#include <common/shader.hpp>
#include "engine/ShaderHandlers/ShaderManager/ShaderManager.h"

#include "engine/Materials/Material.h"

ShaderHandler::ShaderHandler(const string& _vertexShader, const string& _fragShader) : BaseShaderHandler(_vertexShader,_fragShader)
{

}

void ShaderHandler::Initialize()
{
    BaseShaderHandler::Initialize();

    GetUniformLocation(mIsUsingNormalMapHandler, "mUseNormalMap");

    //Get colors handlers
    GetUniformLocation(mColorsHandlers[(int)COLOR_SLOT::AMBIENT], "mAmbient");
    GetUniformLocation(mColorsHandlers[(int)COLOR_SLOT::DIFFUSE], "mDiffuse");
    GetUniformLocation(mColorsHandlers[(int)COLOR_SLOT::SPECULAR], "mSpecular");

    //Get colors handlers
    GetTextureLocation(mTexturesHandlers[(int)TEXTURE_SLOT::ALBEDO], "mAlbedo");
    GetTextureLocation(mTexturesHandlers[(int)TEXTURE_SLOT::NORMAL_MAP], "mNormalMap");
    GetTextureLocation(mTexturesHandlers[(int)TEXTURE_SLOT::METALLIC_MAP], "mMetallicMap");
    GetTextureLocation(mTexturesHandlers[(int)TEXTURE_SLOT::ROUGH_MAP], "mRoughMap");
    GetTextureLocation(mTexturesHandlers[(int)TEXTURE_SLOT::OCCLUSION_MAP], "mOcclusionMap");
    GetTextureLocation(mTexturesHandlers[(int)TEXTURE_SLOT::EMISSIVE_MAP], "mEmissiveMap");
    GetTextureLocation(mTexturesHandlers[(int)TEXTURE_SLOT::HEIGHTMAP], "mHeightmap");

    //Get colors handlers
    GetUniformLocation(mCoeffsHandlers[(int)COEFF_SLOT::METALNESS], "mMetalness");
    GetUniformLocation(mCoeffsHandlers[(int)COEFF_SLOT::ROUGHNESS], "mRoughness");
    GetUniformLocation(mCoeffsHandlers[(int)COEFF_SLOT::OCCLUSIONESS], "mOcclusioness");
    GetUniformLocation(mCoeffsHandlers[(int)COEFF_SLOT::EMISSIVNESS], "mEmissivness");
    GetUniformLocation(mCoeffsHandlers[(int)COEFF_SLOT::HEIGHT], "mHeight");
    GetUniformLocation(mCoeffsHandlers[(int)COEFF_SLOT::TILING], "mTiling");
    GetUniformLocation(mCoeffsHandlers[(int)COEFF_SLOT::SHININESS], "mShininess");
}