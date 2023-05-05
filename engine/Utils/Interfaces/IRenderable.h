#pragma once
#include <map>
using namespace std;

class Mesh;
class Camera;
class BaseMaterial;

class IRenderable
{
public:
    virtual Mesh* GetMesh(int _index) = 0;
    virtual BaseMaterial* GetRendererMaterial(int _index) = 0;
    virtual bool CanBeRendered() const = 0;

public:
    virtual void ChangeMeshByDistance(Camera* _renderingCamera, float _threshold) = 0;
    virtual void Render(Camera* _renderingCamera) = 0;
    virtual void CleanRessources() = 0;
};