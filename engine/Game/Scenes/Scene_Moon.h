#pragma once

#include "engine/Scenes/Scene/Scene.h"

class Ground_Player;
class Landscape;
class Spaceship;
class Trophy;
class DirectionalLight;

class Scene_Moon final : public Scene
{
    bool mCollectibleAvailable = true;
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
    Trophy* CreateTrophy();
    void InitEditorCamera() const;
    void BindCharacterInput();
};