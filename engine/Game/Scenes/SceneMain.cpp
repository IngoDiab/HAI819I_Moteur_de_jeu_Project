#include "SceneMain.h"

#include "engine/Planets/Planet/Planet.h"
#include "engine/Skyboxes/Skybox/Skybox.h"
#include "engine/Components/MeshComponent/MeshComponent.h"
#include "engine/Materials/Material.h"

#include "engine/Game/Player/Player.h"

#include "engine/FilesPath/FilesPath.h"



void SceneMain::LoadScene()
{
    srand(time(NULL));
    Skybox* _skybox = Skybox::Instance();
    _skybox->ChangeSkybox(SPACE_SKYBOX, PNG);

    starSpawnRange = vec3(1000,100,1000);
    starSizeRange = vec2(5,30);

    CreateStars(50);

    Player* _player = CreatePlayer();
}

Player* SceneMain::CreatePlayer()
{
    ObjectManager* _objectManager = ObjectManager::Instance();
    Player* _player = _objectManager->Create<Player>(vec3(0,0,0), vec3(0), vec3(1));
    return _player;
}

Planet* SceneMain::CreateStar(vec3 position, vec3 scale)
{
    ObjectManager* _objectManager = ObjectManager::Instance();
    Planet* _sun = _objectManager->Create<Planet>(position, vec3(0), scale);
    Material* _material = _sun->GetMeshComponent()->GetMaterial(0);
    _material->SetTexture(TEXTURE_SLOT::ALBEDO, "Textures/2D/sun.jpg");
    _material->SetValueCoefficients(COEFF_SLOT::EMISSIVNESS, 1);

    //PointLight* _sunLight = _objectManager->Create<PointLight>();
    return _sun;
}

void SceneMain::CreateStars(int count)
{
    for(int i = 0 ; i < count; i++)
    {
        vec3 pos = vec3( GetRandom11() * starSpawnRange.x , GetRandom11() * starSpawnRange.y , GetRandom11() * starSpawnRange.z);
        float s = starSizeRange.x + ( (starSizeRange.y - starSizeRange.x) * GetRandom01());
        Planet* _star = CreateStar(pos,vec3(s));
        stars.push_back(_star);
        std::cout << pos.x << " " << pos.y << " " << pos.z << std::endl;
    }
}

/*
Planet* SceneMain::CreateEarth(Planet* _parent)
{   
    ObjectManager* _objectManager = ObjectManager::Instance();
    Planet* _earth = _objectManager->Create<Planet>(vec3(25), vec3(0,0,23.44f), vec3(.5), _parent);
    Material* _material = _earth->GetMeshComponent()->GetMaterial(0);
    _material->SetTexture(TEXTURE_SLOT::ALBEDO, "Textures/2D/earth.jpg");
    _earth->SetRevolutionSpeed(5);
    _earth->SetDistanceCenter(50);
    return _earth;
}

Planet* SceneMain::CreateMoon(Planet* _parent)
{
    ObjectManager* _objectManager = ObjectManager::Instance();
    Planet* _moon = _objectManager->Create<Planet>(vec3(5), vec3(0,0,-16.76f), vec3(.5), _parent);
    Material* _material = _moon->GetMeshComponent()->GetMaterial(0);
    _material->SetTexture(TEXTURE_SLOT::ALBEDO, "Textures/2D/moon.jpg");
    _moon->SetRevolutionSpeed(100);
    _moon->SetDistanceCenter(15);
    return _moon;
}*/
