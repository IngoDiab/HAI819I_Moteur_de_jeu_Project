#include "Component.h"

#include "engine/Objects/GameObject/GameObject.h"

void Component::PostConstructor()
{

}

void Component::Update(const float _tickSpeed)
{
    mTransform.Update(_tickSpeed);
}

void Component::LateUpdate(const float _tickSpeed)
{
    mIsDirty = false;
}

void Component::UpdateModelMatrix()
{
    mTransform.UpdateModelMatrix();
}

void Component::Draw3DAxis()
{
    mTransform.Draw3DAxis();
}

void Component::SetOwner(GameObject* _owner)
{
    mOwner = _owner;
    mTransform.SetParentTransform(_owner->GetTransformInstance());
}