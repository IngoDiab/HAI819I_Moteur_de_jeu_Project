#pragma once

#include "ACTION_TYPE.h"
#include "engine/Objects/Object/Object.h"

class Key
{
    int mKeyID = 0;
    ACTION_TYPE mType = ACTION_TYPE::NONE;
    Object* mInstanceCalling = nullptr;
    void* (Object::*mCallback)(bool) = nullptr;
    bool mbIsPressedFirstFrame = false;
    bool mbIsBeingPressed = false;
    bool mbIsReleased = false;

public:
    int GetKeyID() const {return mKeyID;}

    bool HasNotBeenPressed() { return !mbIsPressedFirstFrame && !mbIsBeingPressed && !mbIsReleased;}
    bool HasBeenPressedOnce() { return mbIsPressedFirstFrame && !mbIsBeingPressed && !mbIsReleased;}
    bool HasBeenPressedAtLeastOnce() { return !mbIsReleased && (mbIsPressedFirstFrame || mbIsBeingPressed);}
    bool HasAlreadyBeenReleased() { return !mbIsPressedFirstFrame && !mbIsBeingPressed && mbIsReleased;}

    //bool InstanceCallingHasBeenDeleted() {return !mInstanceCalling;}
    bool InstanceCallingRelativeToScene() {return mInstanceCalling ? mInstanceCalling->GetDurability() == DURABILITY::SCENE : true;}

public:
    Key(){}
    Key(const int _key, const ACTION_TYPE _type, Object* _instanceCalling, void* (Object::*_callback)(bool)) : mKeyID(_key), mType(_type), mInstanceCalling(_instanceCalling), mCallback(_callback){}

public:
    void FirstTimePress() {mbIsPressedFirstFrame = true;}
    void HoldKey() 
    {
        mbIsPressedFirstFrame = false;
        mbIsBeingPressed = true;
    }
    void ReleaseKey() 
    {
        mbIsPressedFirstFrame = false;
        mbIsBeingPressed = false;
        mbIsReleased = true;
    }
    void RebootKey() 
    {
        mbIsReleased = false;
    }

    void ExecuteCallback()
    {
        if(!mCallback || !mInstanceCalling)return;
        switch (mType)
        {
        case ACTION_TYPE::PRESS:
            (mInstanceCalling->*mCallback)(mbIsPressedFirstFrame);
            break;

        case ACTION_TYPE::HOLD:
            (mInstanceCalling->*mCallback)(mbIsBeingPressed);
            break;

        case ACTION_TYPE::RELEASE:
            (mInstanceCalling->*mCallback)(mbIsReleased);
            break;
        
        default:
            break;
        }
    }
};