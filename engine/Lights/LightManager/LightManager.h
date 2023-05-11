#pragma once

#include <vector>

#include <glm/glm.hpp>
using namespace glm;

#include <string>
using namespace std;

#include "engine/Utils/Singleton/Singleton.h"
#include "engine/Objects/Object/Object.h"
class PointLight;
class DirectionalLight;

class LightManager final : public Singleton<LightManager>
{
protected:
	vector<PointLight*> mScenePointLights = vector<PointLight*>();
	vector<DirectionalLight*> mSceneDirectionalLights = vector<DirectionalLight*>();

public:
	vector<PointLight*> GetPointLights() {return mScenePointLights;}
	vector<DirectionalLight*> GetDirectionalLights() {return mSceneDirectionalLights;}

public:
	void AddPointLight(PointLight* _light);
	void AddDirectionalLight(DirectionalLight* _light);

	void RemovePointLight(PointLight* _light);
	void RemoveDirectionalLight(DirectionalLight* _light);

	void DeleteAll();
	void DeleteLightsSpecificDurability(const DURABILITY _durability);
	
	template <typename T>
	bool Exists(vector<T*> _lights, T* _light) const;
};

template <typename T>
bool LightManager::Exists(vector<T*> _lights, T* _light) const
{
    for(T* _lightInScene : _lights)
        if(_lightInScene == _light) return true;
    return false;
}