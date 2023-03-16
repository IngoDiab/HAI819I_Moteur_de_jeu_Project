#pragma once

#include <string>

#include "engine/ShaderHandlers/ShaderHandler/ShaderHandler.h"
#include "engine/Lights/Light/Light.h"
#include "engine/Lights/LightManager/LightManager.h"

struct LightInfo
{
	int positionHandler;
	int colorHandler;
	int intensityHandler;
	int enableHandler;
};

class PhongShaderHandler : public ShaderHandler
{
protected:
	vector<LightInfo*> mLightsHandlers;

public:
    PhongShaderHandler(const string& _vertexShader, const string& _fragShader);

public:
	virtual void SendLights() override;

public:
    virtual void Initialize() override;
};
