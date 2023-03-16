#pragma once

#include <vector>

#include <glm/glm.hpp>
using namespace glm;

#include <string>
using namespace std;

#include "engine/Utils/Singleton/Singleton.h"
#include "engine/Lights/Light/Light.h"

class LightManager final : public Singleton<LightManager>
{
protected:
	vector<Light*> mSceneLights = vector<Light*>();

public:
	void AddLight(Light* _light);
	void RemoveLight(Light* _light);

	bool Exists(Light* _light) const;

	vector<Light*> GetLights() {return mSceneLights;}

public:
	void DeleteLightsSpecificDurability(const DURABILITY _durability);
};