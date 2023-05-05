#pragma once

#include "engine/Scenes/Scene/Scene.h"

class Planet;

class SceneTP2 final : public Scene
{

public:
    virtual void LoadScene() override;

private :
    Planet* CreateSun();
    Planet* CreateEarth(Planet* _parent);
    Planet* CreateMoon(Planet* _parent);
};
