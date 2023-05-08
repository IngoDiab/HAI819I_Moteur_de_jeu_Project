#pragma once

#include "engine/Scenes/Scene/Scene.h"
#include "engine/Game/Player/Player.h"

class Planet;

class SceneMain final : public Scene
{

public:
    virtual void LoadScene() override;

private :
    Planet* CreateSun();
    Planet* CreateEarth(Planet* _parent);
    Planet* CreateMoon(Planet* _parent);
    Player* CreatePlayer();
};
