#include "SceneMain.h"

#include "engine/Planets/Planet/Planet.h"
#include "engine/Physic/BoxCollider/BoxCollider.h"
#include "engine/Skyboxes/Skybox/Skybox.h"
#include "engine/Components/MeshComponent/MeshComponent.h"
#include "engine/Materials/Material.h"
#include "engine/Game/Manager/GameManager.h"

#include "engine/Game/Player/Player.h"

#include "engine/FilesPath/FilesPath.h"
#include "engine/Game/Asteroid/Asteroid.h"
#include "engine/Game/Collectibles/Trophy.h"

void SceneMain::LoadScene()
{
    srand(time(NULL));
    Skybox* _skybox = Skybox::Instance();
    _skybox->ChangeSkybox(SPACE_SKYBOX, PNG);

    CreateSolarSystem();

    Player* _player = CreatePlayer();
}

Player* SceneMain::CreatePlayer()
{
    ObjectManager* _objectManager = ObjectManager::Instance();
    Player* _player = _objectManager->Create<Player>(vec3(0,0,-1200), vec3(0), vec3(1));
    
    return _player;
}

void SceneMain::CreateSolarSystem()
{
    ObjectManager* _objectManager = ObjectManager::Instance();
    Planet* _sun = _objectManager->Create<Planet>(vec3(0), vec3(0), vec3(500));
    Material* _material = _sun->GetMeshComponent()->GetMaterial(0);
    _material->SetTexture(TEXTURE_SLOT::ALBEDO, "Textures/2D/sun.jpg");
    _material->SetValueCoefficients(COEFF_SLOT::EMISSIVNESS, 1);

    PointLight* _sunLight = _objectManager->Create<PointLight>(vec3(0), vec3(0), vec3(1), _sun);
    _sunLight->SetIntensity(500000);

    CreateEarth(_sun);

    int _nbAsteroids = 16;
    mAsteroids.resize(_nbAsteroids);
    CreateAsteroids(_nbAsteroids, _sun->GetWorldPosition(), _sun->GetWorldScale());

    Asteroid* _randomAsteroid = mAsteroids[0];
    _randomAsteroid->GetCollider()->SetOnCollisionCallback([=](CollisionData _data) 
    {
        if(_randomAsteroid->IsMarkedForDestroy()) return;
        CreateTrophy(_randomAsteroid->GetWorldPosition());
        ObjectManager* _objectManager = ObjectManager::Instance();
        _objectManager->Destroy(_randomAsteroid);
    });
}

void SceneMain::CreateAsteroids(int _count, const vec3& _noAsteroidsZoneCenter, const vec3& _noAsteroidsZoneDims)
{
    ObjectManager* _objectManager = ObjectManager::Instance();
    for(int i = 0 ; i < _count; i++)
    {
        float _scale = mAsteroidsSizeRange.x + ( (mAsteroidsSizeRange.y - mAsteroidsSizeRange.x) * GetRandom01());

        float _posX = _noAsteroidsZoneCenter.x + GetRandom11() * mAsteroidsSpawnRange.x;
        _posX += _posX < _noAsteroidsZoneCenter.x ? -_noAsteroidsZoneDims.x - _scale: _noAsteroidsZoneDims.x + _scale;

        float _posY = _noAsteroidsZoneCenter.y + GetRandom11() * mAsteroidsSpawnRange.y;
        _posY += _posY < _noAsteroidsZoneCenter.y ? -_noAsteroidsZoneDims.y - _scale: _noAsteroidsZoneDims.y + _scale;

        float _posZ = _noAsteroidsZoneCenter.z + GetRandom11() * mAsteroidsSpawnRange.z;
        _posZ += _posZ < _noAsteroidsZoneCenter.z ? -_noAsteroidsZoneDims.z - _scale: _noAsteroidsZoneDims.z + _scale;

        vec3 _pos = vec3( _posX, _posY, _posZ);


        Asteroid* _asteroid = CreateAsteroid(_noAsteroidsZoneCenter, _pos, vec3(_scale));
        mAsteroids[i] = _asteroid;
    }
}

Asteroid* SceneMain::CreateAsteroid(const vec3& _centerPos, const vec3& _position, const vec3& _scale)
{
    ObjectManager* _objectManager = ObjectManager::Instance();
    Asteroid* _asteroid = _objectManager->Create<Asteroid>(_position, vec3(GetRandom01()*360, GetRandom01()*360, GetRandom01()*360), _scale);

    PhysicComponent* _asteroidPhysics = _asteroid->GetPhysicComponent();
    _asteroidPhysics->SetVelocity(normalize(_position-_centerPos)*10.f);

    return _asteroid;
}

Trophy* SceneMain::CreateTrophy(const vec3& _position)
{
    if(!mCollectibleAvailable) return nullptr;
    ObjectManager* _objectManager = ObjectManager::Instance();
    Trophy* _trophy = _objectManager->Create<Trophy>(_position);
    _trophy->GetCollider()->SetOnTriggerEnterCallback([=](CollisionData _data) 
    {
        mCollectibleAvailable = false;
        _objectManager->Destroy(_trophy); 
    });

    return _trophy;
}

void SceneMain::CreateEarth(Planet* _parent)
{   
    ObjectManager* _objectManager = ObjectManager::Instance();
    Planet* _earth = _objectManager->Create<Planet>(vec3(0), vec3(0,0,23.44f), vec3(.1f), _parent);
    Material* _material = _earth->GetMeshComponent()->GetMaterial(0);
    _material->SetTexture(TEXTURE_SLOT::ALBEDO, "Textures/2D/earth.jpg");
    _earth->SetRevolutionSpeed(1);
    _earth->SetDistanceCenter(1000);

    CreateMoon(_earth);

    GameManager* _gm = GameManager::Instance();
    _gm->AddScenePlanet(_earth, "Earth");

    BoxCollider* _collider = _earth->GetBoxCollider();
    _collider->SetOnTriggerEnterCallback([=](CollisionData _data) 
    {
        GameManager* _gameManager = GameManager::Instance();
        _gameManager->SetPlanetToEnter(_earth); 
        _gameManager->EnableSpaceTravel(true); 
    });
    _collider->SetOnTriggerExitCallback([=](CollisionData _data) 
    {
        GameManager* _gameManager = GameManager::Instance();
        _gameManager->SetPlanetToEnter(nullptr); 
        _gameManager->EnableSpaceTravel(false);
    });
}

void SceneMain::CreateMoon(Planet* _parent)
{
    ObjectManager* _objectManager = ObjectManager::Instance();
    Planet* _moon = _objectManager->Create<Planet>(vec3(0), vec3(0,0,-16.76f), vec3(.5), _parent);
    Material* _material = _moon->GetMeshComponent()->GetMaterial(0);
    _material->SetTexture(TEXTURE_SLOT::ALBEDO, "Textures/2D/moon.jpg");
    _moon->SetRevolutionSpeed(10);
    _moon->SetDistanceCenter(300);

    GameManager* _gm = GameManager::Instance();
    _gm->AddScenePlanet(_moon, "Moon");
    
    BoxCollider* _collider = _moon->GetBoxCollider();
    _collider->SetOnTriggerEnterCallback([=](CollisionData _data) 
    {
        GameManager* _gameManager = GameManager::Instance();
        _gameManager->SetPlanetToEnter(_moon); 
        _gameManager->EnableSpaceTravel(true); 
    });
    _collider->SetOnTriggerExitCallback([=](CollisionData _data) 
    {
        GameManager* _gameManager = GameManager::Instance();
        _gameManager->SetPlanetToEnter(nullptr); 
        _gameManager->EnableSpaceTravel(false);
    });
}