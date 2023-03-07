#include "engine/Engine/Engine.h"
#include "engine/Scenes/TP1/SceneTP1.h"

int main(int argc, char** argv)
{
    Engine _engine = Engine();
    _engine.Initialize(1920, 1080, "Engine");

    SceneTP1 _sceneTP1 = SceneTP1();
    _engine.AddScene("TP1",&_sceneTP1);

    _engine.LoadScene("TP1");
    _engine.Run();
    return 0;
}
