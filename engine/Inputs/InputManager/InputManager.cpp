#include "InputManager.h"
#include <GLFW/glfw3.h>

#include "engine/Inputs/MouseManager/MouseManager.h"
#include "engine/Objects/Object/Object.h"
//TODO FIX QWERTY -> AZERTY

void InputManager::CheckStateAllKeys(GLFWwindow* _window)
{
    for(Key& _key : mBindedKeys)
    {
        const int _state = glfwGetKey(_window, _key.mKeyID) || glfwGetMouseButton(_window, _key.mKeyID);
        switch (_state)
        {
        case GLFW_PRESS:
            {
                if(_key.HasNotBeenPressed()) _key.FirstTimePress();
                else if(_key.HasBeenPressedOnce()) _key.HoldKey();
            }
            break;

        case GLFW_RELEASE:
            {
                if(_key.HasBeenPressedAtLeastOnce()) _key.ReleaseKey();
                else if(_key.HasAlreadyBeenReleased()) _key.RebootKey();
            }
            break;
        
        default:
            break;
        }

        _key.ExecuteCallback();
    }
}

#include<iostream>
using namespace std;

void InputManager::CheckStateAllAxis(GLFWwindow* _window)
{
    for(Axis& _axis : mBindedAxis)
    {
        const vector<pair<int,int>> _axisID = _axis.GetAxisID();
        for(pair<int,int> _pair : _axisID)
        {
            if(CheckCustomAxis(_axis, _pair)) continue;
            const float _positiveValue = glfwGetKey(_window, _pair.first);
            const float _negativeValue = glfwGetKey(_window, _pair.second);
            if(_positiveValue == 0 && _negativeValue == 0) continue;
            _axis.SetPositiveValue(glfwGetKey(_window, _pair.first));
            _axis.SetNegativeValue(-1*glfwGetKey(_window, _pair.second));
        }
        //cout<<_positiveValue<<endl;
        _axis.ExecuteCallback();
    }
}

bool InputManager::CheckCustomAxis(Axis& _axis, const pair<int,int>& _pair)
{
    const bool _firstIsMouse = _pair.first==MOUSE_X || _pair.first==MOUSE_Y;
    if(!_firstIsMouse) return false;
    if(_pair.first==MOUSE_X)
    {
        const double _xMove = MouseManager::Instance()->GetXMouseMovement();
        TreatMouseMovement(_axis, _xMove);
    }
    else
    {
        const double _yMove = MouseManager::Instance()->GetYMouseMovement();
        TreatMouseMovement(_axis, _yMove);
    }
    return true;
}

void InputManager::TreatMouseMovement(Axis& _axis, const double& _valueMove)
{
    if(_valueMove > 0)
    {
        _axis.SetPositiveValue(_valueMove);
        _axis.SetNegativeValue(0);
    }
    else if(_valueMove < 0)
    {
        _axis.SetPositiveValue(0);
        _axis.SetNegativeValue(_valueMove);
    }
    else
    {
        _axis.SetPositiveValue(0);
        _axis.SetNegativeValue(0);
    }
}

void InputManager::BindKey(const int _keyID, const ACTION_TYPE _type, Object* _instanceCalling,  void* (Object::*_callback)(bool))
{
    mBindedKeys.push_back(Key(_keyID, _type, _instanceCalling, _callback));
}

void InputManager::BindAxis(const vector<pair<int,int>> _keysID, Object* _instanceCalling, void* (Object::*_callback)(float))
{
    mBindedAxis.push_back(Axis(_keysID, _instanceCalling, _callback));
}