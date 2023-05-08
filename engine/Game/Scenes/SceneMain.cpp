#include "SceneMain.h"

#include "engine/Planets/Planet/Planet.h"
#include "engine/Skyboxes/Skybox/Skybox.h"
#include "engine/Components/MeshComponent/MeshComponent.h"
#include "engine/Materials/Material.h"

#include "engine/Game/Player/Player.h"

#include "engine/FilesPath/FilesPath.h"

void SceneMain::LoadScene()
{
    Skybox* _skybox = Skybox::Instance();
    _skybox->ChangeSkybox(SPACE_SKYBOX, PNG);

    Planet* _sun = CreateSun();
    Planet* _earth = CreateEarth(_sun);
    Planet* _moon = CreateMoon(_earth);

    Player* _player = CreatePlayer();
}

Player* SceneMain::CreatePlayer()
{
    ObjectManager* _objectManager = ObjectManager::Instance();
    Player* _player = _objectManager->Create<Player>(vec3(0,0,50), vec3(0), vec3(1));
    return _player;
}

Planet* SceneMain::CreateSun()
{
    ObjectManager* _objectManager = ObjectManager::Instance();
    Planet* _sun = _objectManager->Create<Planet>(vec3(0), vec3(0), vec3(10));
    Material* _material = _sun->GetMeshComponent()->GetMaterial(0);
    _material->SetTexture(TEXTURE_SLOT::ALBEDO, "Textures/2D/sun.jpg");
    _material->SetValueCoefficients(COEFF_SLOT::EMISSIVNESS, 1);

    PointLight* _sunLight = _objectManager->Create<PointLight>();
    return _sun;
}

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
}
