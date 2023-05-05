#include "LightManager.h"

void LightManager::AddLight(PointLight* _light)
{
	if(Exists(_light)) return;
	mSceneLights.push_back(_light);
}

void LightManager::RemoveLight(PointLight* _light)
{
	if(!Exists(_light)) return;
	mSceneLights.erase(find(mSceneLights.begin(), mSceneLights.end(), _light));
}

bool LightManager::Exists(PointLight* _light) const
{
    for(PointLight* _lightInScene : mSceneLights)
        if(_lightInScene == _light) return true;
    return false;
}

// void LightManager::DeleteLightsSpecificDurability(const DURABILITY _durability)
// {
//     vector<Light*> _LigthsToKeep;
//     for(Light* _light : mSceneLights)
//     {   
//         if(!_light) continue;
//         if(_light->GetDurability() == _durability) delete _light;
//         else _LigthsToKeep.push_back(_light);
//     }
//     mSceneLights = _LigthsToKeep;
// }