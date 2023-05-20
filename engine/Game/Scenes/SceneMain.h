#pragma once

#include "engine/Scenes/Scene/Scene.h"
#include "engine/Game/Player/Player.h"

#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace glm;

class Planet;
class Trophy;
class Asteroid;

class SceneMain final : public Scene
{
    bool mCollectibleAvailable = true;
    vec3 mAsteroidsSpawnRange = vec3(1000,100,1000);
    vec2 mAsteroidsSizeRange = vec2(0.1f,0.25f);

    vector<Asteroid*> mAsteroids = vector<Asteroid*>();

public:
    virtual void LoadScene() override;

private :

    float GetRandom01(){return rand() / (float)RAND_MAX;}
    float GetRandom11(){return (((rand() / (float)RAND_MAX) - 0.5f) * 2.0f);}

    void CreateSolarSystem();
    void CreateAsteroids(int _count, const vec3& _noAsteroidsZoneCenter, const vec3& _noAsteroidsZoneDims);
    Asteroid* CreateAsteroid(const vec3& _centerPos, const vec3& _position, const vec3& _scale);
    void CreateEarth(Planet* _parent);
    void CreateMoon(Planet* _parent);

    Player* CreatePlayer();
    Trophy* CreateTrophy(const vec3& _position);
};
