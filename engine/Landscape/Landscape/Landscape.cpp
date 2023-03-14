#include "Landscape.h"
#include "engine/Engine/Engine.h"
#include "engine/Components/MeshComponent/MeshComponent.h"
#include "engine/Landscape/Mesh/LandscapeMesh.h"
#include "engine/Landscape/Material/LandscapeMaterial.h"
#include "engine/Utils/TextureLoader/TextureLoader.h"

Landscape::Landscape()
{
    mMeshComponent = AddComponent<MeshComponent>(vec3(10), vec3(0), vec3(200,1,200));
    mMeshLandscape = mMeshComponent->CreateMesh<LandscapeMesh>();
    mMeshComponent->CreateMaterial<LandscapeMaterial>();
}

void Landscape::Update(const float _deltaTime)
{
    GameObject::Update(_deltaTime);
    RotateLandscape();
}

void Landscape::ApplyHeightmap(const string& _heightmapPath, const float _maxHeight)
{
    mHeightmapPath = _heightmapPath;
    mMaxHeight = _maxHeight;
    int widthImage = 0;
	int heightImage = 0;
	int channels = 1;
    unsigned char* _image = loadImage(_heightmapPath, widthImage, heightImage, channels, 1);
    if(mMeshLandscape) mMeshLandscape->ApplyHeightmap(_image, _maxHeight, widthImage, heightImage, mTransform.GetScale().y);
    freeImage(_image);
}

void Landscape::ChangeResolution(const int _nbVertexWidth, const int _nbVertexLength)
{
    if(!mMeshLandscape) return;
    mMeshLandscape->ChangeResolution(_nbVertexWidth, _nbVertexLength);
    ReApplyHeightmap(mMeshLandscape);
}

void Landscape::IncreaseResolution(const bool _increase)
{
    if(!_increase || !mMeshLandscape) return;
    mMeshLandscape->ChangeResolution(1);
    ReApplyHeightmap(mMeshLandscape);
}

void Landscape::DecreaseResolution(const bool _decrease)
{
    if(!_decrease || !mMeshLandscape) return;
    mMeshLandscape->ChangeResolution(-1);
    ReApplyHeightmap(mMeshLandscape);
}

void Landscape::ReApplyHeightmap(LandscapeMesh* _landscapeMesh)
{
    if(!mMeshLandscape || mHeightmapPath.empty()) return;
    int widthImage = 0;
	int heightImage = 0;
	int channels = 1;
    unsigned char* _image = loadImage(mHeightmapPath, widthImage, heightImage, channels, 1);
    if(mMeshLandscape) mMeshLandscape->ApplyHeightmap(_image, mMaxHeight, widthImage, heightImage, mTransform.GetScale().y);
    freeImage(_image);
}

void Landscape::RotateLandscape()
{
    if(!mCanRotate)return;
    mMeshComponent->GetTransformInstance()->RotateLocalAxisY(mRotateSpeed*Engine::Instance()->DeltaTime());
}