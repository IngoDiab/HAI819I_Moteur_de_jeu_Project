#pragma once

#include <string>
using namespace std;

#include "engine/Utils/Singleton/Singleton.h"

class SkyboxMesh;
class SkyboxMaterial;
class Camera;

class Skybox final : public Singleton<Skybox>
{
    SkyboxMesh* mMesh = nullptr;
    SkyboxMaterial* mMaterial = nullptr;

public:
    Skybox();
    ~Skybox();

public:
    void Draw(Camera* _renderingCamera);
    void ChangeSkybox(const string& _path, const string& _format);
};