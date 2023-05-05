#pragma once

#include <functional> 
#include <map> 
using namespace std;

#include "engine/Components/Component/Component.h"
#include "engine/Utils/Interfaces/IRenderable.h"
#include "engine/Physic/CollisionData/CollisionData.h"


class Collider : public Component, public IRenderable
{
protected:
    bool mCanBeRendered = true;
    bool mIsTrigger = false;
    map<Collider*, CollisionData> mLastFrameColliderInContact = map<Collider*, CollisionData>();
    map<Collider*, CollisionData> mColliderInContact = map<Collider*, CollisionData>();

    function<void(CollisionData)> mCollisionEnterCallback = nullptr;
    function<void(CollisionData)> mCollisionStayCallback = nullptr;
    function<void(CollisionData)> mCollisionExitCallback = nullptr;

    function<void(CollisionData)> mTriggerEnterCallback = nullptr;
    function<void(CollisionData)> mTriggerStayCallback = nullptr;
    function<void(CollisionData)> mTriggerExitCallback = nullptr;

public:
    virtual bool CanBeRendered() const override {return mCanBeRendered;}
    bool IsTrigger() const {return mIsTrigger;}
    virtual vec3 GetCenterInWorld() const {return vec3(0);}

    void SetTrigger(const bool _isTrigger) {mIsTrigger = _isTrigger;}

    //void SetOnCollisionEnterCallback(function<void(CollisionData)> _callback) {mCollisionEnterCallback = _callback;}
    void SetOnCollisionCallback(function<void(CollisionData)> _callback) {mCollisionStayCallback = _callback;}
    //void SetOnCollisionExitCallback(function<void(CollisionData)> _callback) {mCollisionExitCallback = _callback;}

    void SetOnTriggerEnterCallback(function<void(CollisionData)> _callback) {mTriggerEnterCallback = _callback;}
    void SetOnTriggerStayCallback(function<void(CollisionData)> _callback) {mTriggerStayCallback = _callback;}
    void SetOnTriggerExitCallback(function<void(CollisionData)> _callback) {mTriggerExitCallback = _callback;}

    //void ClearOnCollisionEnterCallback() {mCollisionEnterCallback = nullptr;}
    void ClearOnCollisionCallback() {mCollisionStayCallback = nullptr;}
    //void ClearOnCollisionExitCallback() {mCollisionExitCallback = nullptr;}

    void ClearOnTriggerEnter() {mTriggerEnterCallback = nullptr;}
    void ClearOnTriggerStay() {mTriggerStayCallback = nullptr;}
    void ClearOnTriggerExit() {mTriggerExitCallback = nullptr;}

public:
    virtual void ChangeMeshByDistance(Camera* _renderingCamera, float _threshold) override;

public:
    void ProcessCollideCallbacks(Collider* _other, CollisionData _data);
    void ProcessTriggerCallbacks(Collider* _other, CollisionData _data);
    void EndProcessCallbacks();

    //void OnCollisionEnter(CollisionData _data);
    void OnCollisionStay(CollisionData _data);
    //void OnCollisionExit(CollisionData _data);

    void OnTriggerEnter(CollisionData _data);
    void OnTriggerStay(CollisionData _data);
    void OnTriggerExit(CollisionData _data);

protected:
    bool AlreadyInContact(Collider* _collider);
    bool StillInContact(Collider* _collider);
    void AddColliderInContact(Collider* _collider, const CollisionData& _data);
};