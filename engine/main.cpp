#include "engine/Engine/Engine.h"
#include "engine/Game/Scenes/SceneMain.h"
#include "engine/Game/Scenes/Scene_Earth.h"
#include "engine/Game/Scenes/Scene_Moon.h"
#include "engine/Game/Scenes/Scene_Mars.h"

int main(int argc, char** argv)
{
    Engine _engine = Engine(LAUNCH_MOD::GAME, 1920, 1080, "Space Explorer");

    SceneManager* _sceneManager = SceneManager::Instance();
    SceneMain _sceneMain = SceneMain();
    _sceneManager->AddScene("MAIN",&_sceneMain);

    Scene_Earth _earth = Scene_Earth();
    _sceneManager->AddScene("Earth",&_earth);

    Scene_Moon _moon = Scene_Moon();
    _sceneManager->AddScene("Moon",&_moon);

    Scene_Mars _mars = Scene_Mars();
    _sceneManager->AddScene("Mars",&_mars);

    _sceneManager->LoadScene("Mars");
    _engine.Run();
    return 0;
}
