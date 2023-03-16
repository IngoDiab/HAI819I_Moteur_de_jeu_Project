#include "PhongShaderHandler.h"
#include <GL/glew.h>


PhongShaderHandler::PhongShaderHandler(const string& _vertexShader, const string& _fragShader) : ShaderHandler(_vertexShader,_fragShader)
{

}

void PhongShaderHandler::Initialize()
{
    ShaderHandler::Initialize();
    GetTextureLocation(0, "mAlbedo");

    int _index = 0;
    for(Light* _light : LightManager::Instance()->GetLights())
    {
	    LightInfo* _lightInfo = new LightInfo();
	    _lightInfo->positionHandler = glGetUniformLocation(mShaderHandler,("lights["+to_string(_index)+"].position").c_str());
	    _lightInfo->colorHandler = glGetUniformLocation(mShaderHandler,("lights["+to_string(_index)+"].color").c_str());
	    _lightInfo->intensityHandler = glGetUniformLocation(mShaderHandler,("lights["+to_string(_index)+"].intensity").c_str());
	    _lightInfo->enableHandler = glGetUniformLocation(mShaderHandler,("lights["+to_string(_index)+"].enabled").c_str());

	    mLightsHandlers.push_back(_lightInfo);
	    _index++;
	}
}

void PhongShaderHandler::SendLights()
{ 
	int _index = 0;
	for(Light* _light : LightManager::Instance()->GetLights())
    {
    	glUniform3fv(mLightsHandlers[_index]->positionHandler,1,&_light->GetWorldPosition()[0]);
    	glUniform3fv(mLightsHandlers[_index]->colorHandler,1,&_light->GetColor()[0]);
    	glUniform1f(mLightsHandlers[_index]->intensityHandler,_light->GetIntensity());
    	glUniform1i(mLightsHandlers[_index]->enableHandler,_light->GetEnabled());
 		_index++;
    }
}
