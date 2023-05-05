#include "BoxCollider.h"
#include "engine/Meshs/Cube/Cube.h"
#include "engine/Transform/Material/TransformMaterial.h"
#include "engine/Camera/Camera/Camera.h"
#include "engine/ShaderHandlers/BaseShaderHandler/BaseShaderHandler.h"
#include "engine/FilesPath/FilesPath.h"
#include "engine/Engine/Engine.h"
#include "engine/Windows/Window.h"
#include "engine/Physic/SphereCollider/SphereCollider.h"
#include <glm/gtc/matrix_transform.hpp>
#include <limits>

BoxCollider::BoxCollider()
{
    mMeshOOBB = new Cube(true, false, true, false);
    mMeshAABB = new Cube(true, false, true, false);
    mMaterial = new TransformMaterial(COLLIDER_VERTEX, COLLIDER_FRAG);
}

BoxCollider::~BoxCollider()
{
    CleanRessources();
}

void BoxCollider::Update(const float _tickSpeed)
{
    Collider::Update(_tickSpeed);
    UpdateBox();
}

void BoxCollider::UpdateBox()
{
    //Collider matrix
    mColliderMatrix = mOwner->GetTransformInstance()->GetModelMatrix() * translate(mat4(1.0), mCenter) * scale(mat4(1.0), mSize);
    vec4 _centerV4 = mColliderMatrix*vec4(mCenter,1);
    mCenterInWorld = vec3(_centerV4.x, _centerV4.y, _centerV4.z);

    //Update OOBB
    vector<vec3> _positionsOOBB = mMeshOOBB->ModelPositions();
    for(vec3& _position : _positionsOOBB)
    {
        vec4 _positionV4 = mColliderMatrix * vec4(_position, 1.0f);
        _position = vec3(_positionV4.x, _positionV4.y, _positionV4.z);
    }
    mMeshOOBB->SetPositionsVertices(_positionsOOBB);

    //Update AABB
    vector<vec3> _positionsAABB = vector<vec3>(_positionsOOBB.size()); 
    float _xMin = numeric_limits<float>::max(), _yMin = numeric_limits<float>::max(), _zMin = numeric_limits<float>::max();
    float _xMax = numeric_limits<float>::lowest(), _yMax = numeric_limits<float>::lowest(), _zMax = numeric_limits<float>::lowest();
    for(vec3 _position : _positionsOOBB)
    {
        _xMin = (_position.x < _xMin) ? _position.x : _xMin;
        _yMin = (_position.y < _yMin) ? _position.y : _yMin;
        _zMin = (_position.z < _zMin) ? _position.z : _zMin;

        _xMax = (_position.x > _xMax) ? _position.x : _xMax;
        _yMax = (_position.y > _yMax) ? _position.y : _yMax;
        _zMax = (_position.z > _zMax) ? _position.z : _zMax;
    }

    _positionsAABB[0] = vec3(_xMin,_yMin,_zMin); //LeftBotFar
    _positionsAABB[1] = vec3(_xMax,_yMin,_zMin); //RightBotFar
    _positionsAABB[2] = vec3(_xMin,_yMin,_zMax); //LeftBotNear
    _positionsAABB[3] = vec3(_xMax,_yMin,_zMax); //RightBotNear

    _positionsAABB[4] = vec3(_xMax,_yMax,_zMin); //RightTopFar
    _positionsAABB[5] = vec3(_xMin,_yMax,_zMin); //LeftTopFar
    _positionsAABB[6] = vec3(_xMax,_yMax,_zMax); //RightTopNear
    _positionsAABB[7] = vec3(_xMin,_yMax,_zMax); //LeftTopNear

    mMeshAABB->SetPositionsVertices(_positionsAABB);
}

CollisionData BoxCollider::CollideCube(BoxCollider* _other)
{
    CollisionData _data = CollisionData();

    vector<vec3> _cube1 = mMeshAABB->GetPositionsVertices();
    vector<vec3> _cube2 = _other->GetPhysicBox()->GetPositionsVertices();

    float _minXC1 = _cube1[0].x;
    float _minYC1 = _cube1[0].y;
    float _minZC1 = _cube1[0].z;
    float _maxXC1 = _cube1[1].x;
    float _maxYC1 = _cube1[5].y;
    float _maxZC1 = _cube1[2].z;

    float _minXC2 = _cube2[0].x;
    float _minYC2 = _cube2[0].y;
    float _minZC2 = _cube2[0].z;
    float _maxXC2 = _cube2[1].x;
    float _maxYC2 = _cube2[5].y;
    float _maxZC2 = _cube2[2].z;

    bool _collideOnX = (_minXC1 <= _maxXC2 && _maxXC1 >= _minXC2);      
    bool _collideOnY = (_minYC1 <= _maxYC2 && _maxYC1 >= _minYC2);
    bool _collideOnZ = (_minZC1 <= _maxZC2 && _maxZC1 >= _minZC2);

    if(!_collideOnX || !_collideOnY || !_collideOnZ) return _data;
    _data.mAreColliding = true;

    float _minInterX = std::max(_minXC1, _minXC2);
    float _minInterY = std::max(_minYC1, _minYC2);
    float _minInterZ = std::max(_minZC1, _minZC2);
    float _maxInterX = std::min(_maxXC1, _maxXC2);
    float _maxInterY = std::min(_maxYC1, _maxYC2);
    float _maxInterZ = std::min(_maxZC1, _maxZC2);

    float _interX = abs(_maxInterX - _minInterX);
    float _interY = abs(_maxInterY - _minInterY);
    float _interZ = abs(_maxInterZ - _minInterZ);

    bool _fromLeft = mCenterInWorld.x <= _other->GetCenterInWorld().x; 
    bool _fromBottom = mCenterInWorld.y <= _other->GetCenterInWorld().y; 
    bool _fromBack = mCenterInWorld.z <= _other->GetCenterInWorld().z; 

    if(_interX <= _interY && _interX <= _interZ)
    {
        _data.mImpactNormale = vec3((_fromLeft ? -1 : 1), 0, 0);
        _data.mAmountInCollision = _interX;

        float _impactX = mCenterInWorld.x+(_fromLeft ? -_interX : _interX);
        float _impactY = (_fromBottom ? _minInterY + _interY/2.0f: _maxInterY - _interY/2.0f);
        float _impactZ = (_fromBack ? _minInterZ + _interZ/2.0f: _maxInterZ - _interZ/2.0f);
        _data.mImpactPosition = vec3(_impactX, _impactY, _impactZ);
    }
    else if(_interY <= _interZ)
    {
        _data.mImpactNormale = vec3(0, (mCenterInWorld.y <= _other->GetCenterInWorld().y ? -1 : 1), 0);
        _data.mAmountInCollision = _interY;

        float _impactX = (_fromLeft ? _minInterX + _interX/2.0f: _maxInterX - _interX/2.0f);
        float _impactY = mCenterInWorld.y+(_fromBottom ? -_interY : _interY);
        float _impactZ = (_fromBack ? _minInterZ + _interZ/2.0f: _maxInterZ - _interZ/2.0f);
        _data.mImpactPosition = vec3(_impactX, _impactY, _impactZ);
    }
    else
    {
        _data.mImpactNormale = vec3(0, 0, (mCenterInWorld.z <= _other->GetCenterInWorld().z ? -1 : 1));
        _data.mAmountInCollision = _interZ;

        float _impactX = (_fromLeft ? _minInterX + _interX/2.0f: _maxInterX - _interX/2.0f);
        float _impactY = (_fromBottom ? _minInterY + _interY/2.0f: _maxInterY - _interY/2.0f);
        float _impactZ = mCenterInWorld.z+(_fromBottom ? -_interZ : _interZ);
        _data.mImpactPosition = vec3(_impactX, _impactY, _impactZ);
    }

    return _data;
}

CollisionData BoxCollider::CollideSphere(SphereCollider* _other)
{
    return CollisionData();
}

void BoxCollider::Render(Camera* _renderingCamera)
{
    //Calculate MVP
    const mat4& _modelMatrix = mat4(1.0);
    const mat4& _viewMatrix = _renderingCamera->GetViewMatrix();
    const mat4& _projMatrix = _renderingCamera->GetProjectionMatrix();

    //Use Material
    glUseProgram(mMaterial->GetShader()->GetShaderHandler());
    mMaterial->UseMaterial(_modelMatrix, _viewMatrix, _projMatrix);

    Engine::Instance()->GetWindow()->PolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    //Draw
    mRenderAABB ? mMeshAABB->DrawMesh() : mMeshOOBB->DrawMesh();

    Engine::Instance()->GetWindow()->PolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void BoxCollider::CleanRessources()
{
    delete mMeshOOBB;
    delete mMeshAABB;
    delete mMaterial;
}