#pragma once

#include "engine/Components/Component/Component.h"
#include "engine/Utils/Interfaces/IRenderable.h"
#include "engine/Meshs/Mesh/Mesh.h"
#include "engine/Materials/Material.h"

class Camera;

class MeshComponent : public Component, public IRenderable
{
public:
    virtual void Render(Camera* _renderingCamera) override;
    virtual void CleanRessources() override;
    virtual void ChangeTextureMaterial(const int _textureSlot, const string& _texturePath);

public:
    template<typename T>
    T* CreateMesh();

    template<typename T>
    T* CreateMaterial();

    template<typename T>
    T* CreateMaterial(const string& _vertexShader, const string& _fragShader);
};

template<typename T>
T* MeshComponent::CreateMesh()
{
    T* _meshCreated = new T();
    Mesh* _mesh = dynamic_cast<Mesh*>(_mesh);
    if(!_mesh) return nullptr;
    if(mMesh) delete mMesh;
    mMesh = _meshCreated;
    return _meshCreated;
}

template<typename T>
T* MeshComponent::CreateMaterial()
{
    T* _materialCreated = new T();
    Material* _material = dynamic_cast<Material*>(_materialCreated);
    if(!_material) return nullptr;
    if(mMaterial) delete mMaterial;
    mMaterial = _materialCreated;
    _materialCreated->Initialize();
    return _materialCreated;
}

template<typename T>
T* MeshComponent::CreateMaterial(const string& _vertexShader, const string& _fragShader)
{
    T* _materialCreated = new T(_vertexShader, _fragShader);
    Material* _material = dynamic_cast<Material*>(_materialCreated);
    if(!_material) return nullptr;
    if(mMaterial) delete mMaterial;
    mMaterial = _materialCreated;
    _material->Initialize();
    return _materialCreated;
}