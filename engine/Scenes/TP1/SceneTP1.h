#pragma once

#include "engine/Scenes/Scene/Scene.h"

class Landscape;
class OrbitalCamera;

class SceneTP1 final : public Scene
{
    OrbitalCamera* mOrbitalCamera = nullptr;
    Landscape* mLandscape = nullptr;
    bool mIsLandscapeTurningOrbit = false;

public:
    virtual void LoadScene() override;

private :
    Landscape* CreateLandscape();
    void InitEditorCamera() const;
    void InitOrbitalCamera(Landscape* _landscape);
    void BindSceneInput();
    void BindLandscapeInput(Landscape* _landscape) const;
    void TurnLandscapeOrbit(const bool _active);
};
