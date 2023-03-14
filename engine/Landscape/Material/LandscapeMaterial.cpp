#include "LandscapeMaterial.h"
#include "engine/Landscape/ShaderHandler/LandscapeShaderHandler.h"

LandscapeMaterial::LandscapeMaterial()
{
    LandscapeShaderHandler* _shaderHandler = new LandscapeShaderHandler(LANDSCAPE_VERTEX, LANDSCAPE_FRAG);
    _shaderHandler->Initialize();
    SetShader(_shaderHandler);
}

LandscapeMaterial::LandscapeMaterial(const string& _vertexShader, const string& _fragShader)
{
    LandscapeShaderHandler* _shaderHandler = new LandscapeShaderHandler(_vertexShader, _fragShader);
    _shaderHandler->Initialize();
    SetShader(_shaderHandler);
}

void LandscapeMaterial::Initialize()
{
    LoadTexture(0, "Textures/2D/grass.png");
    LoadTexture(1, "Textures/2D/rock.png");
    LoadTexture(2, "Textures/2D/snowrocks.png");
}

void LandscapeMaterial::UseMaterial(const int _typeTexture, const mat4& _model, const mat4& _view, const mat4& _proj)
{
    Material::UseMaterial(_typeTexture, _model, _view, _proj);
    mShader->SendFloat("mHeightGrassRock",mHeightGrassRock);
    mShader->SendFloat("mHeightRockSnow",mHeightRockSnow);
    mShader->SendFloat("mTransitionThreshold",mTransitionThreshold);
    mShader->SendInt("mTiling",mTiling);
}