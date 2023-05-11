#pragma once

#include "engine/Scenes/Scene/Scene.h"

class Ground_Player;
class Landscape;
class Spaceship;
class DirectionalLight;

class Scene_Earth final : public Scene
{
    Ground_Player* mCharacter = nullptr;
    Landscape* mLandscape = nullptr;
    Spaceship* mSpaceship = nullptr;

    DirectionalLight* mSunLight = nullptr;

public:
    virtual void LoadScene() override;

private :
    Ground_Player* CreateCharacter();
    Spaceship* CreateSpaceship();
    Landscape* CreateLandscape();
    void InitEditorCamera() const;
    void BindCharacterInput();
};