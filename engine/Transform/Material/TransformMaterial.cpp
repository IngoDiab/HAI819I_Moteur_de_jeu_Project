#include "TransformMaterial.h"
#include "engine/ShaderHandlers/ShaderHandler/ShaderHandler.h"

TransformMaterial::TransformMaterial(const string& _vertexShader, const string& _fragShader)
{
    ShaderHandler* _shaderHandler = new ShaderHandler(_vertexShader, _fragShader);
    _shaderHandler->Initialize();
    SetShader(_shaderHandler);
}