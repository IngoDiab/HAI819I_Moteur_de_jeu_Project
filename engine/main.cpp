#include "FilesPath/FilesPath.h"
#include "engine/Engine/Engine.h"
#include "engine/Scenes/TP1/SceneTP1.h"
#include "engine/Scenes/TP2/SceneTP2.h"
#include "engine/Scenes/TP3/SceneTP3.h"
#include "engine/Scenes/TP4/SceneTP4.h"

//TODO Keyboard QWERTY->AZERTY
//TODO Renderer unload only scene
//TODO ShaderManager unload only scene

int main(int argc, char** argv)
{
    Engine _engine = Engine();
    _engine.Initialize(1920, 1080, "Engine");

    SceneManager* _sceneManager = SceneManager::Instance();
    SceneTP1 _sceneTP1 = SceneTP1();
    _sceneManager->AddScene("TP1",&_sceneTP1);

    SceneTP2 _sceneTP2 = SceneTP2();
    _sceneManager->AddScene("TP2",&_sceneTP2);

    SceneTP3 _sceneTP3 = SceneTP3();
    _sceneManager->AddScene("TP3",&_sceneTP3);

    SceneTP4 _sceneTP4 = SceneTP4();
    _sceneManager->AddScene("TP4",&_sceneTP4);

    _sceneManager->LoadScene("TP3");
    _engine.Run();
    return 0;
}
