#include "Collider.h"
#include "engine/Utils/Printer/Printer.h"
void Collider::ChangeMeshByDistance(Camera* _renderingCamera, float _threshold)
{

}

void Collider::ProcessCollideCallbacks(Collider* _other, CollisionData _data)
{
    OnCollisionStay(_data);
    // AddColliderInContact(_other, _data);
    // bool _wasAlreadyCollinding = AlreadyInContact(_other);
    // if(_wasAlreadyCollinding) OnCollisionStay(_data);
    // else OnCollisionEnter(_data);
}

void Collider::ProcessTriggerCallbacks(Collider* _other, CollisionData _data)
{
    AddColliderInContact(_other, _data);
    bool _wasAlreadyCollinding = AlreadyInContact(_other);
    if(_wasAlreadyCollinding) OnTriggerStay(_data);
    else OnTriggerEnter(_data);
}

void Collider::EndProcessCallbacks()
{
    for(pair<Collider*, CollisionData> _colliderInContact : mLastFrameColliderInContact)
    {
        if(StillInContact(_colliderInContact.first)) continue; 
        //if(!mIsTrigger && !_colliderInContact.first->IsTrigger()) OnCollisionExit(_colliderInContact.second);
        /*else*/ if(mIsTrigger) OnTriggerExit(_colliderInContact.second);
    }

    mLastFrameColliderInContact = mColliderInContact;
    mColliderInContact.clear();
}

// void Collider::OnCollisionEnter(CollisionData _data)
// {
//     if(!mCollisionEnterCallback) return;
//     mCollisionEnterCallback(_data);
// }

void Collider::OnCollisionStay(CollisionData _data)
{
    if(!mCollisionStayCallback) return;
    mCollisionStayCallback(_data);
}

// void Collider::OnCollisionExit(CollisionData _data)
// {
//     if(!mCollisionExitCallback) return;
//     mCollisionExitCallback(_data);
// }

void Collider::OnTriggerEnter(CollisionData _data)
{
    if(!mTriggerEnterCallback) return;
    mTriggerEnterCallback(_data);
}

void Collider::OnTriggerStay(CollisionData _data)
{
    if(!mTriggerStayCallback) return;
    mTriggerStayCallback(_data);
}

void Collider::OnTriggerExit(CollisionData _data)
{
    if(!mTriggerExitCallback) return;
    mTriggerExitCallback(_data);
}

bool Collider::AlreadyInContact(Collider* _collider)
{
    for(pair<Collider*, CollisionData> _colliderInContact : mLastFrameColliderInContact)
        if(_collider == _colliderInContact.first) return true;
    return false;
}

bool Collider::StillInContact(Collider* _collider)
{
    for(pair<Collider*, CollisionData> _colliderInContact : mColliderInContact)
        if(_collider == _colliderInContact.first) return true;
    return false;
}

void Collider::AddColliderInContact(Collider* _collider, const CollisionData& _data)
{
    if(StillInContact(_collider)) return;
    mColliderInContact[_collider] = _data;
}

// void Collider::DeleteTriggerInContact(Collider* _trigger)
// {
//     if(!AlreadyInContact(_trigger)) return;
//     mTriggerInContact.erase(find(mTriggerInContact.begin(), mTriggerInContact.end(), _trigger));
// }