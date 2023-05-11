#pragma once

#include "engine/Utils/Singleton/Singleton.h"
#include "engine/Objects/Object/Object.h"
#include <string>
#include <map>
using namespace std;

class Planet;

class GameManager : public Singleton<GameManager>, public Object
{
    Planet* mPlanetToEnter = nullptr;
    bool mCanSpaceTravel = false;
    map<Planet*,string> mScenePlanets = map<Planet*,string>();

public:
    void SetPlanetToEnter(Planet* _planet) {mPlanetToEnter = _planet;}
    void EnableSpaceTravel(bool _enable) { mCanSpaceTravel = _enable;}

public:
    void AddScenePlanet(Planet* _planet, const string& _name);
    void EnterPlanet(bool _pressed);
    void SpaceTravel(bool _pressed);
};