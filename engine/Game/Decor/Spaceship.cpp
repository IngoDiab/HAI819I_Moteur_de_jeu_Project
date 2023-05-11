#include "Spaceship.h"
#include "engine/Planets/Planet/Planet.h"
#include "engine/Meshs/Sphere/Sphere.h"
#include "engine/Materials/Material.h"
#include "engine/Components/MeshComponent/MeshComponent.h"
#include "engine/Physic/PhysicComponent/PhysicComponent.h"
#include "engine/Physic/BoxCollider/BoxCollider.h"

#include "engine/Game/Manager/GameManager.h"
#include "engine/FilesPath/FilesPath.h"

Spaceship::Spaceship()
{
    mMeshComponent = AddComponent<MeshComponent>(vec3(0), vec3(0), vec3(20));
    mMeshComponent->CreateMesh<Mesh>("3DModels/Spaceship/scene.gltf");

    mBoxCollider = AddComponent<BoxCollider>();
    mBoxCollider->SetSize(vec3(550,50,500));
    mBoxCollider->SetCenter(vec3(0,20,0));
    mBoxCollider->SetTrigger(true);
    mBoxCollider->SetOnTriggerEnterCallback([&](CollisionData _data) 
    {
        GameManager* _gameManager = GameManager::Instance();
        _gameManager->EnableSpaceTravel(true); 
    });
    mBoxCollider->SetOnTriggerExitCallback([&](CollisionData _data) 
    {
        GameManager* _gameManager = GameManager::Instance();
        _gameManager->EnableSpaceTravel(false); 
    });
    mPhysicComponent = AddComponent<PhysicComponent>();
    mPhysicComponent->SetStatic(true);
    mPhysicComponent->EnableGravity(false);

    ModifyMaterialAttributes();
}

void Spaceship::ModifyMaterialAttributes()
{
    int _nbMaterials = mMeshComponent->GetNbMaterials();
    for(int i = 0; i < _nbMaterials; ++i)
    {
        Material* _material = mMeshComponent->GetMaterial(i);
        if(!_material) return;
        _material->SetColor(COLOR_SLOT::AMBIENT, vec3(0.05f));
        _material->SetColor(COLOR_SLOT::SPECULAR, vec3(1));
        _material->SetValueCoefficients(COEFF_SLOT::SHININESS, 50);
    }
}

void Spaceship::ClipToLandscape(Landscape* const _landscape)
{
    if(!mPhysicComponent) return;
    mPhysicComponent->ActiveClip(true);
    mPhysicComponent->EnableGravity(false);
    mPhysicComponent->ClipObject(_landscape);
}