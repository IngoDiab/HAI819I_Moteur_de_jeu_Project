#include "LightManager.h"

void LightManager::AddLight(Light* _light)
{
	if(Exists(_light)) return;
	mSceneLights.push_back(_light);
}

void LightManager::RemoveLight(Light* _light)
{
	if(!Exists(_light)) return;
	mSceneLights.erase(find(mSceneLights.begin(), mSceneLights.end(), _light));
}

bool LightManager::Exists(Light* _light) const
{
    for(Light* _lightInScene : mSceneLights)
        if(_lightInScene == _light) return true;
    return false;
}

void LightManager::DeleteLightsSpecificDurability(const DURABILITY _durability)
{
    vector<Light*> _LToKeep;
    for(Light* _light : mSceneLights)
    {   
        if(!_light) continue;
        if(_light->GetDurability() == _durability) delete _light;
        else _LToKeep.push_back(_light);
    }
    mSceneLights = _LToKeep;
}