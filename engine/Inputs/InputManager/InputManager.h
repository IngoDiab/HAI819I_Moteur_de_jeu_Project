#pragma once

#include "engine/Inputs/Type/ACTION_TYPE.h"
#include "engine/Inputs/Tokens/InputCoreTokens.h"
#include "engine/Inputs/Type/Key.h"
#include "engine/Inputs/Type/Axis.h"
#include "engine/Utils/Singleton/Singleton.h"

class GLFWwindow;

class InputManager final : public Singleton<InputManager>
{
    vector<Key> mBindedKeys = vector<Key>();
    vector<Axis> mBindedAxis = vector<Axis>();

public:
    void DeleteObsoleteInputs();

public:
    void CheckStateAllKeys(GLFWwindow* _window);
    void CheckStateAllAxis(GLFWwindow* _window);
    bool CheckCustomAxis(Axis& _axis, const pair<int,int>& _pair);
    void TreatMouseMovement(Axis& _axis, const double& _valueMove);
    void BindKey(const int _keyID, const ACTION_TYPE _type, Object* _instanceCalling, void* (Object::*_callback)(bool));
    void BindAxis(const vector<pair<int,int>> _keysID, Object* _instanceCalling, void* (Object::*_callback)(float));
};