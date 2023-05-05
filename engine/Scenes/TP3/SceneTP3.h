#pragma once

#include "engine/Scenes/Scene/Scene.h"

class Character;
class Landscape;

class SceneTP3 final : public Scene
{
    Character* mCharacter = nullptr;
    Landscape* mLandscape = nullptr;

public:
    virtual void LoadScene() override;

private :
    Character* CreateCharacter();
    Landscape* CreateLandscape();
    void InitEditorCamera() const;
    void BindCharacterInput();
    void BindLandscapeInput() const;
};
