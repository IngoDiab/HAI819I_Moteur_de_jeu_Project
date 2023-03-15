#include "MeshComponent.h"

#include "engine/Meshs/Mesh/Mesh.h"
#include "engine/Materials/Material.h"
#include "engine/ShaderHandlers/ShaderHandler/ShaderHandler.h"
#include "engine/Camera/Camera/Camera.h"

void MeshComponent::Render(Camera* _renderingCamera)
{
    //Calculate MVP
    const mat4& _modelMatrix = mTransform.GetModelMatrix();
    const mat4& _viewMatrix = _renderingCamera->GetViewMatrix();
    const mat4& _projMatrix = _renderingCamera->GetProjectionMatrix();

    //Use Material
    glUseProgram(mMaterial->GetShader()->GetShaderHandler());
    mMaterial->UseMaterial(GL_TEXTURE_2D, _modelMatrix, _viewMatrix, _projMatrix);

    //Draw
    mMesh->DrawMesh();
}

void MeshComponent::CleanRessources()
{
    delete mMesh;
    delete mMaterial;
}

void MeshComponent::ChangeTextureMaterial(const int _textureSlot, const string& _texturePath)
{
    if(!mMaterial) return;
    mMaterial->LoadTexture(_textureSlot, _texturePath);
}