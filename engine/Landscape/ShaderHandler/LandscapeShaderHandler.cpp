#include "LandscapeShaderHandler.h"
#include <GL/glew.h>

#include <iostream>
using namespace std;

LandscapeShaderHandler::LandscapeShaderHandler(const string& _vertexShader, const string& _fragShader) : ShaderHandler(_vertexShader,_fragShader)
{

}

void LandscapeShaderHandler::Initialize()
{
    ShaderHandler::Initialize();
    GetTextureLocation(0, "mGrassTex");
    GetTextureLocation(1, "mRockTex");
    GetTextureLocation(2, "mSnowrockTex");

    GetNumericalLocation("mHeightGrassRock");
    GetNumericalLocation("mHeightRockSnow");
    GetNumericalLocation("mTransitionThreshold");
    GetNumericalLocation("mTiling");
}
