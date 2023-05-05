#pragma once

#include <vector>

#include <glm/glm.hpp>
using namespace glm;

#include <string>
using namespace std;

#include "engine/Utils/Singleton/Singleton.h"
#include "engine/Lights/PointLight/PointLight.h"

class LightManager final : public Singleton<LightManager>
{
protected:
	vector<PointLight*> mSceneLights = vector<PointLight*>();

public:
	vector<PointLight*> GetLights() {return mSceneLights;}

public:
	void AddLight(PointLight* _light);
	void RemoveLight(PointLight* _light);
	bool Exists(PointLight* _light) const;

// public:
// 	void DeleteLightsSpecificDurability(const DURABILITY _durability);
};