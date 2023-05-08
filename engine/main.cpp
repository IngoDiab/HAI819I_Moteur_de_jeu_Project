#include "FilesPath/FilesPath.h"
#include "engine/Engine/Engine.h"
#include "engine/Game/Scenes/SceneMain.h"
//TODO Keyboard QWERTY->AZERTY
//TODO Renderer unload only scene
//TODO ShaderManager unload only scene

int main(int argc, char** argv)
{
    Engine _engine = Engine();
    _engine.Initialize(1920, 1080, "Engine");

    SceneManager* _sceneManager = SceneManager::Instance();
    SceneMain _sceneMain = SceneMain();
    _sceneManager->AddScene("MAIN",&_sceneMain);

    _sceneManager->LoadScene("MAIN");
    _engine.Run();
    return 0;
}
