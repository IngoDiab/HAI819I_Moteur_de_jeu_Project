#pragma once

#include "engine/Scenes/Scene/Scene.h"
#include "engine/Game/Player/Player.h"

#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace glm;

class Planet;

class SceneMain final : public Scene
{
    vec3 starSpawnRange;
    vec2 starSizeRange;

    vector<Planet*> stars;

public:
    virtual void LoadScene() override;

private :

    float GetRandom01(){return rand() / (float)RAND_MAX;}
    float GetRandom11(){return (((rand() / (float)RAND_MAX) - 0.5f) * 2.0f);}

    void CreateStars(int count);
    Planet* CreateStar(vec3 position, vec3 scale);


    Planet* CreateEarth(Planet* _parent);
    Planet* CreateMoon(Planet* _parent);
    Player* CreatePlayer();
};
