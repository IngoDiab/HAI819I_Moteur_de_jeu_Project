#include "engine/Engine/Engine.h"
#include "engine/Game/Scenes/SceneMain.h"
#include "engine/Game/Scenes/Scene_Earth.h"
//TODO Keyboard QWERTY->AZERTY
//TODO Renderer unload only scene
//TODO ShaderManager unload only scene

int main(int argc, char** argv)
{
    Engine _engine = Engine(LAUNCH_MOD::GAME, 1920, 1080, "Engine");

    SceneManager* _sceneManager = SceneManager::Instance();
    SceneMain _sceneMain = SceneMain();
    _sceneManager->AddScene("MAIN",&_sceneMain);

    Scene_Earth _earth = Scene_Earth();
    _sceneManager->AddScene("Earth",&_earth);

    _sceneManager->LoadScene("MAIN");
    _engine.Run();
    return 0;
}
