#include "SceneTP2.h"

#include "engine/Planets/Planet/Planet.h"

#include "engine/Components/MeshComponent/MeshComponent.h"
#include "engine/Planets/Material/EarthMaterial/EarthMaterial.h"
#include "engine/Planets/Material/MoonMaterial/MoonMaterial.h"
#include "engine/Planets/Material/SunMaterial/SunMaterial.h"

void SceneTP2::LoadScene()
{
    mSkybox = new Skybox();
    mSkybox->ChangeSkybox("Textures/Skybox/Space/", ".png");

    ObjectManager* _objectManager = ObjectManager::Instance();
    Planet* _sun = _objectManager->Create<Planet>(vec3(0), vec3(0), vec3(10));
    _sun->GetMeshComponent()->CreateMaterial<SunMaterial>();

    Planet* _earth = _objectManager->Create<Planet>(vec3(25), vec3(0,0,23.44f), vec3(.5), _sun);
    _earth->GetMeshComponent()->CreateMaterial<EarthMaterial>();
    _earth->SetRevolutionSpeed(5);
    _earth->SetDistanceCenter(50);

    Planet* _moon = _objectManager->Create<Planet>(vec3(5), vec3(0,0,-16.76f), vec3(.5), _earth);
    _moon->GetMeshComponent()->CreateMaterial<MoonMaterial>();
    _moon->SetRevolutionSpeed(100);
    _moon->SetDistanceCenter(15);
}