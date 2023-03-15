#include "SceneTP2.h"

#include "engine/Planets/Planet/Planet.h"
#include "engine/Skyboxes/Skybox/Skybox.h"
#include "engine/Components/MeshComponent/MeshComponent.h"
#include "engine/Planets/Material/PlanetMaterial.h"

void SceneTP2::LoadScene()
{
    Skybox* _skybox = Skybox::Instance();
    _skybox->ChangeSkybox("Textures/Skybox/Space4K/", ".png");

    ObjectManager* _objectManager = ObjectManager::Instance();
    Planet* _sun = _objectManager->Create<Planet>(vec3(0), vec3(0), vec3(10));
    _sun->GetMeshComponent()->CreateMaterial<PlanetMaterial>();
    _sun->GetMeshComponent()->ChangeTextureMaterial(0, "Textures/2D/sun.jpg");

    Planet* _earth = _objectManager->Create<Planet>(vec3(25), vec3(0,0,23.44f), vec3(.5), _sun);
    _earth->GetMeshComponent()->CreateMaterial<PlanetMaterial>();
    _earth->GetMeshComponent()->ChangeTextureMaterial(0, "Textures/2D/earth.jpg");
    _earth->SetRevolutionSpeed(5);
    _earth->SetDistanceCenter(50);

    Planet* _moon = _objectManager->Create<Planet>(vec3(5), vec3(0,0,-16.76f), vec3(.5), _earth);
    _moon->GetMeshComponent()->CreateMaterial<PlanetMaterial>();
    _moon->GetMeshComponent()->ChangeTextureMaterial(0, "Textures/2D/moon.jpg");
    _moon->SetRevolutionSpeed(100);
    _moon->SetDistanceCenter(15);
}