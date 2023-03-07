#include "SkyboxShaderHandler.h"
#include <GL/glew.h>

SkyboxShaderHandler::SkyboxShaderHandler(const string& _vertexShader, const string& _fragShader) : ShaderHandler(_vertexShader,_fragShader)
{

}

void SkyboxShaderHandler::Initialize()
{
    ShaderHandler::Initialize();
    GetTextureLocation(0, "skybox");
}
