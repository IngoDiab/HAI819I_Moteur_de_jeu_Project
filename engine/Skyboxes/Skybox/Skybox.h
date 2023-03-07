#pragma once

#include "engine/Utils/Singleton/Singleton.h"

class SkyboxMesh;
class SkyboxMaterial;
class Camera;

#define SKYBOX_VERTEX "Skyboxes/Shader/Skybox_vertex.glsl"
#define SKYBOX_FRAG "Skyboxes/Shader/Skybox_frag.glsl"

class Skybox final : public Singleton<Skybox>
{
    SkyboxMesh* mMesh = nullptr;
    SkyboxMaterial* mMaterial = nullptr;

public:
    Skybox();
    ~Skybox();

public:
    void Draw(Camera* _renderingCamera);
};