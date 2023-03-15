#include "GameObject.h"

#include "engine/Engine/Engine.h"
#include "engine/Scenes/Scene/Scene.h"
#include "engine/Scenes/SceneManager/SceneManager.h"

GameObject::GameObject()
{}

GameObject::~GameObject()
{
    DeleteComponents();
}

GameObject::GameObject(const Transform& _transform) : mTransform(_transform)
{}

GameObject::GameObject(const vec3& _positions, const vec3& _rotations, const vec3& _scale) : mTransform(_positions, _rotations, _scale)
{}

void GameObject::Update(const float _tickSpeed)
{
    mTransform.Update(_tickSpeed);
    for(Component* _component : mComponents)
        _component->Update(_tickSpeed);
    for(GameObject* _child : mChildren)
        _child->Update(_tickSpeed);
}

void GameObject::UpdateModelMatrix()
{
    mTransform.UpdateModelMatrix();
    for(Component* _component : mComponents)
        _component->UpdateModelMatrix();
    for(GameObject* _child : mChildren)
        _child->UpdateModelMatrix();
}

void GameObject::LateUpdate(const float _tickSpeed)
{
    for(Component* _component : mComponents)
        _component->LateUpdate(_tickSpeed);
    for(GameObject* _child : mChildren)
        _child->LateUpdate(_tickSpeed);
}

Scene* GameObject::GetWorld()
{
    return SceneManager::Instance()->GetCurrentScene();
}

float GameObject::GetInSceneDeltaTime()
{
    return Engine::Instance()->DeltaTime()*GetWorld()->GetTickSpeed()*mTickSpeed;
}

void GameObject::SetParent(GameObject* _gameobject)
{
    const bool _parentIsAlreadyNullptr = !_gameobject && !mParent;
    const bool _parentAlreadyHasThisChild = _gameobject && _gameobject->HasChild(this);
    if(_parentIsAlreadyNullptr || _parentAlreadyHasThisChild) return;

    const bool _changeParentToNullptr = mParent && !_gameobject;
    const bool _changeParentToGameObject = !mParent && _gameobject;

    //Remove current parent-child link
    if(mParent) mParent->DeleteChild(this);

    //Link child with parent
    mParent = _gameobject;
    mTransform.SetParentTransform(_gameobject ? _gameobject->GetTransformInstance() : nullptr);

    //Link parent with child
    if(mParent) mParent->AddChildren(this);

    //Add/Remove from scene's child list
    ObjectManager* _instance = ObjectManager::Instance();
    if(_changeParentToNullptr) _instance->AddGameObject(this);
    if(_changeParentToGameObject) _instance->RemoveGameObject(this);
}

void GameObject::Draw3DAxis()
{
    mTransform.Draw3DAxis();
    for(Component* _component : mComponents)
        _component->Draw3DAxis();
    for(GameObject* _child : mChildren)
        _child->Draw3DAxis();
}

bool GameObject::HasChild(GameObject* _child) const
{
    for(GameObject* _objectChild : mChildren)
        if(_objectChild == _child) return true;
    return false;
}

void GameObject::AddChildren(GameObject* _child)
{
    if(HasChild(_child)) return;
    mChildren.push_back(_child);
}

void GameObject::DeleteChild(GameObject* _child)
{
    if(HasChild(_child)) return;
    mChildren.erase(find(mChildren.begin(), mChildren.end(), _child));
}

void GameObject::DeleteComponents()
{
    for(Component* _component : mComponents)
        if(_component) delete _component;
    mComponents.clear();
}

void GameObject::RotateLocalAxisX(const float _rotate)
{
    mTransform.RotateLocalAxisX(_rotate);//*_rotationSpeed*Engine::Instance()->DeltaTime());
}

void GameObject::RotateLocalAxisY(const float _rotate)
{
    mTransform.RotateLocalAxisY(_rotate);
}

void GameObject::RotateLocalAxisZ(const float _rotate)
{
    mTransform.RotateLocalAxisZ(_rotate);
}