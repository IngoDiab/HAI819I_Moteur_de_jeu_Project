#include "SkyboxShaderHandler.h"
#include <GL/glew.h>

SkyboxShaderHandler::SkyboxShaderHandler(const string& _vertexShader, const string& _fragShader) : BaseShaderHandler(_vertexShader,_fragShader)
{
}

void SkyboxShaderHandler::Initialize()
{
    BaseShaderHandler::Initialize();

    //Get Skybox handler
    GetTextureLocation(mCubemapHandler, "mCubemap");
}
