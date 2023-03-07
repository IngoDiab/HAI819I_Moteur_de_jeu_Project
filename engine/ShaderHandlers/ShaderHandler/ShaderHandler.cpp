#include "ShaderHandler.h"
#include <GL/glew.h>
#include <common/shader.hpp>
#include "engine/ShaderHandlers/ShaderManager/ShaderManager.h"

ShaderHandler::ShaderHandler(const string& _vertexShader, const string& _fragShader)
{
    mShaderHandler = ShaderManager::Instance()->LoadShader(ShaderInfo(_vertexShader, _fragShader));
}

void ShaderHandler::Initialize()
{
    mModelHandler = glGetUniformLocation(mShaderHandler, "model");
    mViewHandler = glGetUniformLocation(mShaderHandler, "view");
    mProjectionHandler = glGetUniformLocation(mShaderHandler, "projection");
}

void ShaderHandler::SendMVP(const mat4& _model, const mat4& _view, const mat4& _proj)
{
    glUniformMatrix4fv(mModelHandler, 1, GL_FALSE, &_model[0][0]);
    glUniformMatrix4fv(mViewHandler, 1, GL_FALSE, &_view[0][0]);
    glUniformMatrix4fv(mProjectionHandler, 1, GL_FALSE, &_proj[0][0]);
}

void ShaderHandler::SendTexture(int _typeTexture, int _offsetSlot, int _texture)
{
    int _textureShaderHandler = mTexturesHandlers[_offsetSlot];
    if(_textureShaderHandler == -1 || _texture == 0)return;
    glActiveTexture(GL_TEXTURE0 + _offsetSlot);
    glBindTexture(_typeTexture, _texture);
    glUniform1i(_textureShaderHandler, _offsetSlot);
}

void ShaderHandler::GetTextureLocation(const int _slotTexture, const string& _nameLocation)
{
    mTexturesHandlers[_slotTexture] = glGetUniformLocation(mShaderHandler, _nameLocation.c_str());
}

void ShaderHandler::GetNumericalLocation(const string& _nameLocation)
{
    int _slotFloat = glGetUniformLocation(mShaderHandler, _nameLocation.c_str());
    if(_slotFloat == -1) return;
    mNumericalHandlers[_nameLocation] = _slotFloat;
}

void ShaderHandler::SendFloat(const string& _nameLocation, float _value)
{
    for(pair<string, int> _locations : mNumericalHandlers)
    {
        if(_nameLocation != _locations.first) continue;
        glUniform1f(_locations.second, _value);
    }
}

void ShaderHandler::SendInt(const string& _nameLocation, int _value)
{
    for(pair<string, int> _locations : mNumericalHandlers)
    {
        if(_nameLocation != _locations.first) continue;
        glUniform1i(_locations.second, _value);
    }
}