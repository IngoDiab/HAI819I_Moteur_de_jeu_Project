#pragma once

#include <map>
using namespace std;

#include "engine/Utils/Singleton/Singleton.h"

#include<string>
using namespace std;

struct ShaderInfo
{
    string mVertexShader;
    string mFragmentShader;

    ShaderInfo(){}
    ShaderInfo(const string& _vertexShader, const string& _fragShader)
    {
        mVertexShader = _vertexShader;
        mFragmentShader = _fragShader;
    }

    bool operator==(const ShaderInfo& _other) const
    {
        return mVertexShader == _other.mVertexShader && mFragmentShader == _other.mFragmentShader;
    }

    bool operator<(const ShaderInfo& _other) const
    {
        return mVertexShader < _other.mVertexShader && mFragmentShader < _other.mFragmentShader;
    }
};


class ShaderManager final : public Singleton<ShaderManager>
{
    map<ShaderInfo, unsigned int> mShaders = map<ShaderInfo, unsigned int>();

public:
    ~ShaderManager();

public:
    unsigned int LoadShader(const ShaderInfo& _shader);

    void AddShader(const ShaderInfo& _shader, const unsigned int _shaderHandle);
    void DeleteShader(const ShaderInfo& _shader);
    void DeleteAllShaders();

    bool Exists(const ShaderInfo& _shader);
    unsigned int GetShader(const ShaderInfo& _shader);
};