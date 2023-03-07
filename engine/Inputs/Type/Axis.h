#pragma once

#include <vector>
using namespace std;

#include "engine/Objects/Object/Object.h"

class Axis
{
    //Positive/Negative
    vector<pair<int,int>> mAxisID = vector<pair<int,int>>();
    Object* mInstanceCalling = nullptr;
    void* (Object::*mCallback)(float) = nullptr;

    float mPositiveValue = 0;
    float mNegativeValue = 0;

public:
    vector<pair<int,int>> GetAxisID() const {return mAxisID;}
    void SetPositiveValue(const float _value){mPositiveValue = _value;}
    void SetNegativeValue(const float _value){mNegativeValue = _value;}

public:
    Axis(){}
    Axis(vector<pair<int,int>> _keysID, Object* _instanceCalling, void* (Object::*_callback)(float)) : mAxisID(_keysID), mInstanceCalling(_instanceCalling), mCallback(_callback){}

    void ExecuteCallback()
    {
        if(!mCallback || !mInstanceCalling)return;
        (mInstanceCalling->*mCallback)(mPositiveValue+mNegativeValue);
        mPositiveValue = 0;
        mNegativeValue = 0;
    }
};