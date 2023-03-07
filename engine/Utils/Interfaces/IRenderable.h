#pragma once

class Mesh;
class Camera;
class Material;

class IRenderable
{
protected:
    Mesh* mMesh = nullptr;
    Material* mMaterial = nullptr;
    bool mCanBeRendered = true;

public:
    Mesh* GetMesh(){return mMesh;}
    void SetMesh(Mesh* const _mesh){mMesh = _mesh;}

    Material* GetMaterial(){return mMaterial;}
    void SetMaterial(Material* const _material){mMaterial = _material;}

    bool CanBeRendered() const {return mCanBeRendered;}
    void SetCanBeRendered(const bool _canBeRendered) {mCanBeRendered = _canBeRendered;}

public:
    virtual void Render(Camera* _renderingCamera) = 0;
    virtual void CleanRessources() = 0;
};