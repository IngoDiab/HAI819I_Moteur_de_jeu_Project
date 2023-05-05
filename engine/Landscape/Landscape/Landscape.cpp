#include "Landscape.h"
#include "engine/Engine/Engine.h"
#include "engine/Landscape/Mesh/LandscapeMesh.h"
#include "engine/Landscape/Material/LandscapeMaterial.h"
#include "engine/ShaderHandlers/BaseShaderHandler/BaseShaderHandler.h"
#include "engine/Physic/BoxCollider/BoxCollider.h"
#include "engine/Physic/PhysicComponent/PhysicComponent.h"

Landscape::Landscape()
{
    CreateLandscapeMesh();
    CreateLandscapeMaterial();
    mBoxCollider = AddComponent<BoxCollider>();
    mPhysicComponent = AddComponent<PhysicComponent>();
    mPhysicComponent->EnableGravity(false);
    mPhysicComponent->SetStatic(true);
}

Landscape::~Landscape()
{
    CleanRessources();
}

void Landscape::Update(const float _deltaTime)
{
    GameObject::Update(_deltaTime);
    RotateLandscape();
}

void Landscape::ChangeMeshByDistance(Camera* _renderingCamera, float _threshold)
{
    double _distanceCamera = length(_renderingCamera->GetWorldPosition()-mTransform.GetTransformData()->mWorldPosition);
    for(pair<double,LandscapeMesh*> _pair : mLODS)
    {
        double _distanceRequired = _pair.first;
        if(_distanceRequired+_threshold >= _distanceCamera) return;
        mMesh = _pair.second;
    }
}

void Landscape::Render(Camera* _renderingCamera)
{
    if(!mCanBeRendered) return;
    
    //Calculate MVP
    const mat4& _modelMatrix = mTransform.GetModelMatrix();
    const mat4& _viewMatrix = _renderingCamera->GetViewMatrix();
    const mat4& _projMatrix = _renderingCamera->GetProjectionMatrix();

    //Use Material
    glUseProgram(mMaterial->GetShader()->GetShaderHandler());
    mMaterial->UseMaterial(_modelMatrix, _viewMatrix, _projMatrix);

    //Draw
    ChangeMeshByDistance(_renderingCamera, 25);
    mMesh->DrawMesh();
}

void Landscape::CleanRessources()
{
    delete mMesh;
    delete mMaterial;
}

void Landscape::ApplyHeightmap(const string& _heightmapPath, const float _maxHeight, const float _shift)
{
    if(mHeightmap) freeImage(mHeightmap);
    mMaxHeight = _maxHeight/256.f;
	int channels = 1;
    mHeightmap = loadImage(_heightmapPath, mWidthImage, mHeightImage, channels, 1);
    mMaterial->SetHeightmap(_heightmapPath, mMaxHeight);
    mMaterial->SetShift(_shift);
}

void Landscape::ChangeResolution(const int _nbVertexWidth, const int _nbVertexLength)
{
    if(!mMesh) return;
    mMesh->ChangeResolution(_nbVertexWidth, _nbVertexLength);
}

void Landscape::IncreaseResolution(const bool _increase)
{
    if(!_increase || !mMesh) return;
    mMesh->ChangeResolution(1);
}

void Landscape::DecreaseResolution(const bool _decrease)
{
    if(!_decrease || !mMesh) return;
    mMesh->ChangeResolution(-1);
}

//TODO REFACTOR
void Landscape::GetProjectionOnPlane(vec3& _pointToProject, float _offset)
{
    if(!mMesh) return;
    mat4 _modelMatrix = mTransform.GetModelMatrix();

    vec4 _origineWorld4 = _modelMatrix * vec4(mMesh->GetPositonVertex(0,0, true, true),1);
    vec4 _cornerUWorld4 = _modelMatrix * vec4(mMesh->GetPositonVertex(1,0, true, true),1);
    vec4 _cornerVWorld4 = _modelMatrix * vec4(mMesh->GetPositonVertex(0,1, true, true),1);

    vec4 _u4 = _cornerUWorld4-_origineWorld4;
    vec3 _uVector = vec3(_u4.x, _u4.y, _u4.z);
    
    vec4 _v4 = _cornerVWorld4-_origineWorld4;
    vec3 _vVector = vec3(_v4.x, _v4.y, _v4.z);

    vec3 _origineWorld = vec3(_origineWorld4.x, _origineWorld4.y, _origineWorld4.z);
    vec3 _normal = normalize(cross(_uVector, _vVector));
    
    const float _dotDirectionProjNormalPlan = dot(vec3(0,-1,0), _normal);
    if(_dotDirectionProjNormalPlan == 0 || !std::isfinite(_dotDirectionProjNormalPlan)) return;

    const float _dotOriginProjNormalPlan = dot(_pointToProject, _normal);
    const float _dotPointPlanNormalPlan = dot(_origineWorld, _normal);

    const float _result = (_dotPointPlanNormalPlan-_dotOriginProjNormalPlan)/_dotDirectionProjNormalPlan;


    const vec3 _resultPos = _pointToProject + _result*vec3(0,-1,0);
    
    vec2 _uv = UV(_resultPos-_origineWorld, _uVector, _vVector);

    vec4 _bottomLeft4 = _modelMatrix * vec4(mMesh->GetPositonVertex(_uv.x,_uv.y, false, false),1);
    vec4 _bottomRight4 = _modelMatrix * vec4(mMesh->GetPositonVertex(_uv.x,_uv.y, true, false),1);
    vec4 _upLeft4 = _modelMatrix * vec4(mMesh->GetPositonVertex(_uv.x,_uv.y, false, true),1);
    vec4 _upRight4 = _modelMatrix * vec4(mMesh->GetPositonVertex(_uv.x,_uv.y, true, true),1);

    vec3 _bottomLeft = vec3(_bottomLeft4.x, _bottomLeft4.y, _bottomLeft4.z);
    vec3 _bottomRight = vec3(_bottomRight4.x, _bottomRight4.y, _bottomRight4.z);
    vec3 _upLeft = vec3(_upLeft4.x, _upLeft4.y, _upLeft4.z);
    vec3 _upRight = vec3(_upRight4.x, _upRight4.y, _upRight4.z);

    float _u0, _u1, _u2;
    if(InTriangle(_resultPos, _bottomLeft, _bottomRight, _upRight, _u0, _u1, _u2))
    {
        vec2 _bottomLeftUV = mMesh->GetUVVertex(_uv.x,_uv.y, false, false);
        vec2 _bottomRightUV = mMesh->GetUVVertex(_uv.x,_uv.y, true, false);
        vec2 _upRightUV = mMesh->GetUVVertex(_uv.x,_uv.y, true, true);

        double _height = _u0*TexelByUV(_bottomLeftUV)+_u1*TexelByUV(_bottomRightUV)+_u2*TexelByUV(_upRightUV);
        _pointToProject = _resultPos + vec3(0,_height+_offset-mMaterial->GetShift(),0);
    }
    else if(InTriangle(_resultPos, _bottomLeft, _upRight, _upLeft, _u0, _u1, _u2))
    {
        vec2 _bottomLeftUV = mMesh->GetUVVertex(_uv.x,_uv.y, false, false);
        vec2 _upRightUV = mMesh->GetUVVertex(_uv.x,_uv.y, true, true);
        vec2 _upLeftUV = mMesh->GetUVVertex(_uv.x,_uv.y, false, true);

        double _height = _u0*TexelByUV(_bottomLeftUV)+_u1*TexelByUV(_upRightUV)+_u2*TexelByUV(_upLeftUV);
        _pointToProject = _resultPos + vec3(0,_height+_offset-mMaterial->GetShift(),0);
    }
}

bool Landscape::InTriangle(vec3 _point, vec3 _v0, vec3 _v1, vec3 _v2, float& _u0, float& _u1, float& _u2)
{
    vec3 _edge01 = _v1 - _v0;
    vec3 _edge02 = _v2 - _v0;
    vec3 _normal = cross(_edge02, _edge01);
    float _area = length(_normal)/2.f;
    _normal = normalize(_normal);

    {
        vec3 _edge12 = _v2 - _v1;
        vec3 _edge1P = _point - _v1;
        vec3 _resultingNormal = cross(_edge1P, _edge12);
        vec3 _resultingNormalNormalized = normalize(_resultingNormal);
        float _area12P = length(_resultingNormal)/2.f;
        float _dotNormales = dot(_normal,_resultingNormalNormalized);
        _u0 = (_dotNormales < 0 ? -1 : 1) * _area12P/_area; //
    }

    {
        vec3 _edge20 = _v0 - _v2;
        vec3 _edge2P = _point - _v2;
        vec3 _resultingNormal = cross(_edge2P, _edge20);
        vec3 _resultingNormalNormalized = normalize(_resultingNormal);
        float _area20P = length(_resultingNormal)/2.f;
        float _dotNormales = dot(_normal,_resultingNormalNormalized);
        _u1 = (_dotNormales < 0 ? -1 : 1) * _area20P/_area;
    }

    {
        vec3 _edge01 = _v1 - _v0;
        vec3 _edge0P = _point - _v0;
        vec3 _resultingNormal = cross(_edge0P, _edge01);
        vec3 _resultingNormalNormalized = normalize(_resultingNormal);
        float _area01P = length(_resultingNormal)/2.f;
        float _dotNormales = dot(_normal,_resultingNormalNormalized);
        _u2 = (_dotNormales < 0 ? -1 : 1) * _area01P/_area;
    }

    return _u0 >= 0 && _u0 <= 1 && _u1 >= 0 && _u1 <= 1 && _u2 >= 0 && _u2 <= 1;
}

vec2 Landscape::UV(const vec3& _posOnPlan, const vec3& _uVector, const vec3& _vVector)
{
    vec2 _uv;
    _uv.x = (dot(normalize(_uVector), _posOnPlan))/_uVector.x;
    _uv.y = (dot(normalize(_vVector), _posOnPlan))/_vVector.z;

    _uv.x = _uv.x < 0 ? 0 : _uv.x > 1 ? 1 : _uv.x;
    _uv.y = _uv.y < 0 ? 0 : _uv.y > 1 ? 1 : _uv.y;
    return _uv;
}

double Landscape::TexelByUV(const vec2& _uv)
{
    const long _lineIndex = _uv.y* mHeightImage;
    const long _columnIndex = _uv.x* mWidthImage;
    const long _index = _lineIndex* mWidthImage + _columnIndex;
    const double _texelValue = mHeightmap[_index]/255.;
    const float _yPos = _texelValue*mMaxHeight;
    return _yPos;
}

void Landscape::RotateLandscape()
{
    if(!mCanRotate)return;
    mTransform.RotateLocalAxisY(mRotateSpeed*Engine::Instance()->DeltaTime());
}

void Landscape::CreateLandscapeMesh()
{
    mMesh = new LandscapeMesh();
    for(pair<double,LandscapeMesh*> _pair : mLODS)
    {
        delete _pair.second;
    }
    mLODS.clear();

    mLODS[0] = mMesh;
}

void Landscape::CreateLandscapeMaterial()
{
    if(mMaterial) delete mMaterial;
    mMaterial = new LandscapeMaterial();
}