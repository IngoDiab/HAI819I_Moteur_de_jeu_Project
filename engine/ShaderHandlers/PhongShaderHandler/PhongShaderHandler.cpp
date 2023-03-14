#include "PhongShaderHandler.h"
#include <GL/glew.h>

PhongShaderHandler::PhongShaderHandler(const string& _vertexShader, const string& _fragShader) : ShaderHandler(_vertexShader,_fragShader)
{

}

void PhongShaderHandler::Initialize()
{
    ShaderHandler::Initialize();
    GetTextureLocation(0, "mAlbedo");
}
