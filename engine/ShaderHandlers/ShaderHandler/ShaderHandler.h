#pragma once
#include<string>
#include <vector>
#include <map>
using namespace std;

#include <glm/glm.hpp>
using namespace glm;

class ShaderHandler
{
protected:
    int mShaderHandler;
    int mModelHandler;
    int mViewHandler;
    int mProjectionHandler;

    vector<int> mTexturesHandlers = vector<int>(16);
    map<string, int> mNumericalHandlers = map<string, int>();

public:
    ShaderHandler(const string& _vertexShader, const string& _fragShader);

public:
    unsigned int GetShaderHandler() const {return mShaderHandler;}

public:
    virtual void Initialize();

    virtual void SendMVP(const mat4& _model, const mat4& _view, const mat4& _proj);

    virtual void SendTexture(int _typeTexture, int _offsetSlot, int _texture);
    virtual void GetTextureLocation(const int _slotTexture, const string& _nameLocation);

    virtual void GetNumericalLocation(const string& _nameLocation);
    virtual void SendFloat(const string& _nameLocation, float _value);
    virtual void SendInt(const string& _nameLocation, int _value);
};
