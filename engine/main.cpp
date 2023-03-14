#include "engine/Engine/Engine.h"
#include "engine/Scenes/TP1/SceneTP1.h"
#include "engine/Scenes/TP2/SceneTP2.h"

#include <iostream>
using namespace std;

int main(int argc, char** argv)
{
    Engine _engine = Engine();
    _engine.Initialize(1920, 1080, "Engine");

    SceneManager* _sceneManager = SceneManager::Instance();
    SceneTP1 _sceneTP1 = SceneTP1();
    _sceneManager->AddScene("TP1",&_sceneTP1);

    SceneTP2 _sceneTP2 = SceneTP2();
    _sceneManager->AddScene("TP2",&_sceneTP2);

    _sceneManager->LoadScene("TP2");
    _engine.Run();
    return 0;
}
