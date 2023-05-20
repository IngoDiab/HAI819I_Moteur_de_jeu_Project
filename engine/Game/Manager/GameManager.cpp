#include "GameManager.h"
#include "engine/Scenes/SceneManager/SceneManager.h"

void GameManager::AddScenePlanet(Planet* _planet, const string& _name)
{
    mScenePlanets[_planet] = _name;
}

void GameManager::EnterPlanet(bool _pressed)
{
    if(!mPlanetToEnter || !_pressed) return;
    string _nameLoadScene = mScenePlanets[mPlanetToEnter];
    mPlanetToEnter = nullptr;
    if(_nameLoadScene == "") return;
    SceneManager::Instance()->LoadScene(_nameLoadScene);
}

void GameManager::SpaceTravel(bool _pressed)
{
    if(!mCanSpaceTravel || !_pressed) return;
    mCanSpaceTravel = false;
    SceneManager::Instance()->LoadScene("MAIN");
}