#include "Skybox.h"
#include "engine/Skyboxes/Mesh/SkyboxMesh.h"
#include "engine/Skyboxes/ShaderHandler/SkyboxShaderHandler.h"
#include "engine/Skyboxes/Material/SkyboxMaterial.h"
#include "engine/Camera/Camera/Camera.h"

Skybox::Skybox()
{
    mMesh = new SkyboxMesh();
    mMaterial = new SkyboxMaterial(SKYBOX_VERTEX, SKYBOX_FRAG);
    mMaterial->Initialize();
}

Skybox::~Skybox()
{
    delete mMesh;
    delete mMaterial;
}

void Skybox::Draw(Camera* _renderingCamera)
{
    //Calculate VP
    const mat4& _viewMatrix = _renderingCamera->GetViewMatrix();
    const mat4& _projMatrix = _renderingCamera->GetProjectionMatrix();

    //Use Material
    glUseProgram(mMaterial->GetShader()->GetShaderHandler());
    mMaterial->UseMaterial(GL_TEXTURE_CUBE_MAP, mat4(1.0), _viewMatrix, _projMatrix);

    //Draw
    mMesh->DrawMesh();
}

void Skybox::ChangeSkybox(const string& _path, const string& _format)
{
    if(mMaterial) mMaterial->ChangeSkyboxTextures(_path, _format);
}