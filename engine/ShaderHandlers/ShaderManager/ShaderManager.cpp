#include "ShaderManager.h"
#include <GL/glew.h>
#include <common/shader.hpp>

ShaderManager::~ShaderManager()
{
    DeleteAllShaders();
}

unsigned int ShaderManager::LoadShader(const ShaderInfo& _shader)
{
    if(Exists(_shader)) return GetShader(_shader);
    unsigned int _shaderHandler = LoadShaders(_shader.mVertexShader.c_str(), _shader.mFragmentShader.c_str());
    mShaders[_shader] = _shaderHandler;
    return _shaderHandler;
}

void ShaderManager::AddShader(const ShaderInfo& _shader, const unsigned int _shaderHandle)
{
    if(Exists(_shader))return;
    mShaders[_shader] = _shaderHandle;
}

void ShaderManager::DeleteShader(const ShaderInfo& _shader)
{
    if(!Exists(_shader))return;
    glDeleteShader(mShaders[_shader]);
}

void ShaderManager::DeleteAllShaders()
{
    for(pair<ShaderInfo, unsigned int> _shaderPair : mShaders)
        glDeleteShader(_shaderPair.second);
}

bool ShaderManager::Exists(const ShaderInfo& _shader)
{
    for(pair<ShaderInfo, unsigned int> _registeredShader : mShaders)
        if(_shader == _registeredShader.first) return true;
    return false;
}

unsigned int ShaderManager::GetShader(const ShaderInfo& _shader)
{
    return mShaders[_shader];
}