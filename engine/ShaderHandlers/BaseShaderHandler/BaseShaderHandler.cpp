#include "BaseShaderHandler.h"
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include <common/shader.hpp>
#include "engine/ShaderHandlers/ShaderManager/ShaderManager.h"
#include "engine/Lights/LightManager/LightManager.h"

#define NB_POINT_LIGHTS 16

BaseShaderHandler::BaseShaderHandler(const string& _vertexShader, const string& _fragShader)
{
    mShaderHandler = ShaderManager::Instance()->LoadShader(ShaderInfo(_vertexShader, _fragShader));
}

void BaseShaderHandler::Initialize()
{
    mModelHandler = glGetUniformLocation(mShaderHandler, "model");
    mViewHandler = glGetUniformLocation(mShaderHandler, "view");
    mProjectionHandler = glGetUniformLocation(mShaderHandler, "projection");

    mCameraPositionHandler = glGetUniformLocation(mShaderHandler, "cameraPosition");
    mSkyboxHandler = glGetUniformLocation(mShaderHandler, "skybox");

    mPointLightHandlers.resize(NB_POINT_LIGHTS);

    for(int i = 0; i < NB_POINT_LIGHTS; ++i)
    {
        PointLightHandlers _pointLightHandlers = mPointLightHandlers[i];
        mPointLightHandlers[i].mPositionHandler = glGetUniformLocation(mShaderHandler, ("mPointLights["+to_string(i)+"].mLightPos").c_str());
        mPointLightHandlers[i].mColorHandler = glGetUniformLocation(mShaderHandler, ("mPointLights["+to_string(i)+"].mLightColor").c_str());
        mPointLightHandlers[i].mPowerHandler = glGetUniformLocation(mShaderHandler, ("mPointLights["+to_string(i)+"].mLightPower").c_str());
        mPointLightHandlers[i].mIsEnabledHandler = glGetUniformLocation(mShaderHandler, ("mPointLights["+to_string(i)+"].mIsEnabled").c_str());
    }
}

void BaseShaderHandler::SendMVP(const mat4& _model, const mat4& _view, const mat4& _proj)
{
    glUniformMatrix4fv(mModelHandler, 1, GL_FALSE, &_model[0][0]);
    glUniformMatrix4fv(mViewHandler, 1, GL_FALSE, &_view[0][0]);
    glUniformMatrix4fv(mProjectionHandler, 1, GL_FALSE, &_proj[0][0]);
}

void BaseShaderHandler::SendLights()
{
    LightManager* _lightManager = LightManager::Instance();
    vector<PointLight*> _pointLights = _lightManager->GetLights();
    for(int i = 0; i < NB_POINT_LIGHTS && i<_pointLights.size(); ++i)
    {
        PointLightHandlers _pointLightHandlers = mPointLightHandlers[i];
        PointLight* _pointLight = _pointLights[i];
        glUniform3fv(_pointLightHandlers.mPositionHandler, 1, glm::value_ptr(_pointLight->GetWorldPosition()));
        glUniform3fv(_pointLightHandlers.mColorHandler, 1, glm::value_ptr(_pointLight->GetColor()));
        glUniform1f(_pointLightHandlers.mPowerHandler, _pointLight->GetIntensity());
        glUniform1i(_pointLightHandlers.mIsEnabledHandler, _pointLight->IsEnabled());
    }
}

void BaseShaderHandler::SendTexture(int _typeTexture, int _offsetSlot, unsigned int _texture, int _handler)
{
    if(_handler == -1 || _texture == 0)return;
    glActiveTexture(GL_TEXTURE0 + _offsetSlot);
    glBindTexture(_typeTexture, _texture);
    glUniform1i(_handler, _offsetSlot);
}

void BaseShaderHandler::GetTextureLocation(int& _slotTexture, const string& _nameLocation)
{
    _slotTexture = glGetUniformLocation(mShaderHandler, _nameLocation.c_str());
}

void BaseShaderHandler::GetUniformLocation(int& _slotUniform, const string& _nameLocation)
{
    _slotUniform = glGetUniformLocation(mShaderHandler, _nameLocation.c_str());
}

void BaseShaderHandler::SendFloat(float _value, int _handler)
{
    if(_handler == -1) return;
    glUniform1f(_handler, _value);
}

void BaseShaderHandler::SendInt(int _value, int _handler)
{
    if(_handler == -1) return;
    glUniform1i(_handler, _value);
}

void BaseShaderHandler::SendVec3(vec3 _value, int _handler)
{
    if(_handler == -1) return;
    glUniform3fv(_handler, 1, value_ptr(_value));
}

void BaseShaderHandler::SendBool(bool _value, int _handler)
{
    if(_handler == -1) return;
    glUniform1i(_handler, _value);
}