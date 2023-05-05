#pragma once 

#include <vector>
using namespace std;

#include <algorithm>

#include "engine/Objects/Object/Object.h"
#include "engine/Renderer/Renderer.h"
#include "engine/Physic/PhysicManager/PhysicManager.h"
#include "engine/Transform/Transform.h"
#include "engine/Utils/Interfaces/ITickable.h"
#include "engine/Utils/Interfaces/IRenderable.h"
#include "engine/Physic/PhysicComponent/PhysicComponent.h"
#include "engine/Components/Component/Component.h"
#include "engine/Physic/Collider/Collider.h"

class Camera;
class Scene;

class GameObject : public Object, public ITickable
{
protected:
    bool mIsDirty = true;
    unsigned int mID;
    Transform mTransform;
    GameObject* mParent = nullptr;
    vector<GameObject*> mChildren = vector<GameObject*>();
    vector<Component*> mComponents = vector<Component*>();

public :
    GameObject();
    virtual ~GameObject();
    GameObject(const Transform& _transform);
    GameObject(const vec3& _positions, const vec3& _rotations, const vec3& _scale);

public:
    bool IsDirty() const {return mIsDirty;}

    unsigned int GetID() const {return mID;}
    void SetID(const unsigned int _id) {mID = _id;}
    
    Transform* GetTransformInstance() {return &mTransform;}
    TransformData GetTransform() const {return mTransform.GetTransformData();}

    vec3 GetWorldPosition() const {return GetTransform().mWorldPosition;}
    vec3 GetLocalPosition() const {return GetTransform().mLocalPosition;}
    void SetPosition(const vec3& _position) {mTransform.GetTransformData()->mLocalPosition = _position;}

    vec3 GetWorldRotation() const {return GetTransform().mWorldRotation;}
    vec3 GetLocalRotation() const {return GetTransform().mLocalRotation;}
    void SetRotation(const vec3& _rotation) {mTransform.GetTransformData()->mLocalRotation = _rotation;}

    vec3 GetWorldScale() const {return GetTransform().mWorldScale;}
    vec3 GetLocalScale() const {return GetTransform().mLocalScale;}
    virtual void SetScale(const vec3& _scale) {mTransform.GetTransformData()->mLocalScale = _scale;}
    
    GameObject* GetParent() const {return mParent;}
    void SetParent(GameObject* _gameobject);

    vector<GameObject*> GetChildren() const {return mChildren;}

public:
    virtual void Update(const float _tickSpeed) override;
    //void UpdateModelMatrix();
    virtual void LateUpdate(const float _tickSpeed) override;

    Scene* GetWorld();
    float GetInSceneDeltaTime();

    void Draw3DAxis();

private:
    bool HasChild(GameObject* _child) const;
    void AddChildren(GameObject* _child);
    void DeleteChild(GameObject* _child);
    void DeleteComponents();

public:
    virtual void RotateLocalAxisX(const float _rotate);
    virtual void RotateLocalAxisY(const float _rotate);
    virtual void RotateLocalAxisZ(const float _rotate);

public:
    template<typename T>
    T* AddComponent(const vec3& _position = vec3(0), const vec3& _rotation = vec3(0), const vec3& _scale = vec3(1));

    //return first found T component
    template<typename T>
    T* GetComponent();

    template<typename T>
    void DeleteComponent();
};

template<typename T>
T* GameObject::AddComponent(const vec3& _position, const vec3& _rotation, const vec3& _scale)
{
    T* _object = new T();

    Component* _component = dynamic_cast<Component*>(_object);
    if(!_component)
    {
        delete _object;
        return nullptr;
    }
    mComponents.push_back(_component);
    _component->SetOwner(this);
    _component->SetPosition(_position);
    _component->SetRotation(_rotation);
    _component->SetScale(_scale);

    _component->PostConstructor();

    IRenderable* _componentRenderable = dynamic_cast<IRenderable*>(_object);
    if(_componentRenderable) Renderer::Instance()->AddRenderable(_componentRenderable);

    PhysicComponent* _componentPhysic = dynamic_cast<PhysicComponent*>(_object);
    if(_componentPhysic) 
    {
        PhysicManager::Instance()->AddPhysicComponent(_componentPhysic);
        _componentPhysic->SetReadyToCollide(true);
    }

    return _object;
}

template<typename T>
T* GameObject::GetComponent()
{
    for(Component* _component : mComponents)
    {
        T* _castedComp = dynamic_cast<T*>(_component);
        if(!_castedComp) continue;
        return _castedComp;
    }
    return nullptr;
}

template<typename T>
void GameObject::DeleteComponent()
{
    for(Component* _component : mComponents)
    {
        T* _castedComp = dynamic_cast<T*>(_component);
        if(!_castedComp) continue;
        mComponents.erase(find(mComponents.begin(), mComponents.end(), _component));
        delete _component;
    }
}