#include "LightManager.h"
#include "engine/Lights/PointLight/PointLight.h"
#include "engine/Lights/DirectionalLight/DirectionalLight.h"

void LightManager::AddPointLight(PointLight* _light)
{
	if(Exists(mScenePointLights, _light)) return;
	mScenePointLights.push_back(_light);
}

void LightManager::AddDirectionalLight(DirectionalLight* _light)
{
	if(Exists(mSceneDirectionalLights, _light)) return;
	mSceneDirectionalLights.push_back(_light);
}

void LightManager::RemovePointLight(PointLight* _light)
{
	if(!Exists(mScenePointLights, _light)) return;
	mScenePointLights.erase(remove(mScenePointLights.begin(), mScenePointLights.end(), _light), mScenePointLights.end());
}

void LightManager::RemoveDirectionalLight(DirectionalLight* _light)
{
	if(!Exists(mSceneDirectionalLights, _light)) return;
	mSceneDirectionalLights.erase(remove(mSceneDirectionalLights.begin(), mSceneDirectionalLights.end(), _light), mSceneDirectionalLights.end());
}

void LightManager::DeleteAll()
{
	mScenePointLights.clear();
	mSceneDirectionalLights.clear();
}

void LightManager::DeleteLightsSpecificDurability(const DURABILITY _durability)
{
    vector<PointLight*> _pointLigthsToKeep;
    for(PointLight* _light : mScenePointLights)
    {   
        if(!_light) continue;
        if(_light->GetDurability() == _durability) delete _light;
        else _pointLigthsToKeep.push_back(_light);
    }
    mScenePointLights = _pointLigthsToKeep;

	vector<DirectionalLight*> _directionalLigthsToKeep;
    for(DirectionalLight* _light : mSceneDirectionalLights)
    {   
        if(!_light) continue;
        if(_light->GetDurability() == _durability) delete _light;
        else _directionalLigthsToKeep.push_back(_light);
    }
    mSceneDirectionalLights = _directionalLigthsToKeep;
}