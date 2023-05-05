#pragma once

#include <vector>
using namespace std;

#include "engine/Utils/Singleton/Singleton.h"
#include "engine/Utils/Interfaces/IRenderable.h"

class Camera;

class Renderer final : public Singleton<Renderer>
{
    vector<IRenderable*> mRenderableObjects = vector<IRenderable*>();
    bool mCanDraw3DAxis = true;

public:
    void AddRenderable(IRenderable* _renderable);
    // void DeleteRenderables();
    void DrawObjects(Camera* _camera);
    void Draw3DAxis();
};