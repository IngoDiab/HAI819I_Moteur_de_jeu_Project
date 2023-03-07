#include "Landscape.h"
#include "engine/Landscape/Mesh/LandscapeMesh.h"
#include "engine/Camera/Camera/Camera.h"
#include "engine/ShaderHandlers/ShaderHandler/ShaderHandler.h"
#include "engine/Landscape/Material/LandscapeMaterial.h"
#include "engine/Utils/TextureLoader/TextureLoader.h"

Landscape::Landscape()
{
    mMesh = new LandscapeMesh(2, 2);
    mMaterial = new LandscapeMaterial(LANDSCAPE_VERTEX, LANDSCAPE_FRAG);
    mMaterial->Initialize();
}

Landscape::Landscape(const int _nbVertexWidth, const int _nbVertexLength)
{
    mMesh = new LandscapeMesh(_nbVertexWidth, _nbVertexLength);
    mMaterial = new LandscapeMaterial(LANDSCAPE_VERTEX, LANDSCAPE_FRAG);
    mMaterial->Initialize();
}

Landscape::Landscape(const vec3& _positions, const vec3& _rotations, const vec3& _scale)
{
    mTransform = Transform(_positions, _rotations, _scale);
    mMesh = new LandscapeMesh(2, 2);
    mMaterial = new LandscapeMaterial(LANDSCAPE_VERTEX, LANDSCAPE_FRAG);
    mMaterial->Initialize();
}

void Landscape::Update(const float _deltaTime)
{
    GameObject::Update(_deltaTime);
    RotateLandscape();
}

void Landscape::Render(Camera* _renderingCamera)
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

    // glDisableVertexAttribArray(0);
    // glDisableVertexAttribArray(1);
    //
}

void Landscape::CleanRessources()
{
    delete mMesh;
    delete mMaterial;
}

void Landscape::ApplyHeightmap(const string& _heightmapPath, const float _maxHeight)
{
    mHeightmapPath = _heightmapPath;
    mMaxHeight = _maxHeight;
    int widthImage = 0;
	int heightImage = 0;
	int channels = 1;
    unsigned char* _image = loadImage(_heightmapPath, widthImage, heightImage, channels, 1);
    LandscapeMesh* _landscapeMesh = dynamic_cast<LandscapeMesh*>(mMesh);
    if(_landscapeMesh) _landscapeMesh->ApplyHeightmap(_image, _maxHeight, widthImage, heightImage, mTransform.GetScale().y);
    freeImage(_image);
}

void Landscape::ChangeResolution(const int _nbVertexWidth, const int _nbVertexLength)
{
    LandscapeMesh* _landscapeMesh = dynamic_cast<LandscapeMesh*>(mMesh);
    if(!_landscapeMesh) return;
    _landscapeMesh->ChangeResolution(_nbVertexWidth, _nbVertexLength);
    ReApplyHeightmap(_landscapeMesh);
}

void Landscape::IncreaseResolution(const bool _increase)
{
    if(!_increase) return;
    LandscapeMesh* _landscapeMesh = dynamic_cast<LandscapeMesh*>(mMesh);
    if(!_landscapeMesh)return;
    _landscapeMesh->ChangeResolution(1);
    ReApplyHeightmap(_landscapeMesh);
}

void Landscape::DecreaseResolution(const bool _decrease)
{
    if(!_decrease) return;
    LandscapeMesh* _landscapeMesh = dynamic_cast<LandscapeMesh*>(mMesh);
    if(!_landscapeMesh)return;
    _landscapeMesh->ChangeResolution(-1);
    ReApplyHeightmap(_landscapeMesh);
}

void Landscape::ReApplyHeightmap(LandscapeMesh* _landscapeMesh)
{
    if(!_landscapeMesh || mHeightmapPath.empty()) return;
    int widthImage = 0;
	int heightImage = 0;
	int channels = 1;
    unsigned char* _image = loadImage(mHeightmapPath, widthImage, heightImage, channels, 1);
    if(_landscapeMesh) _landscapeMesh->ApplyHeightmap(_image, mMaxHeight, widthImage, heightImage, mTransform.GetScale().y);
    freeImage(_image);
}

void Landscape::RotateLandscape()
{
    if(!mCanRotate)return;
    RotateY(1, mRotateSpeed);
}