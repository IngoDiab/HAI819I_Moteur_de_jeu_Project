#pragma once

#include<string>
#include <vector>
#include <map>
using namespace std;

#include <glm/glm.hpp>
using namespace glm;

struct PointLightHandlers
{
    int mPositionHandler;
    int mColorHandler;
    int mPowerHandler;
    int mIsEnabledHandler;
};

class BaseShaderHandler
{
protected:
    int mShaderHandler;
    int mModelHandler;
    int mViewHandler;
    int mProjectionHandler;

    int mCameraPositionHandler;
    int mSkyboxHandler;

    vector<PointLightHandlers> mPointLightHandlers;

public:
    BaseShaderHandler(const string& _vertexShader, const string& _fragShader);

public:
    unsigned int GetShaderHandler() const {return mShaderHandler;}

public:
    virtual void Initialize();

    virtual void SendMVP(const mat4& _model, const mat4& _view, const mat4& _proj);
    void SendLights();

    virtual void GetTextureLocation(int& _slotTexture, const string& _nameLocation);
    virtual void GetUniformLocation(int& _slotUniform, const string& _nameLocation);

    void SendTexture(int _typeTexture, int _offsetSlot, unsigned int _texture, int _handler);
    void SendFloat(float _value, int _handler);
    void SendInt(int _value, int _handler);
    void SendVec3(vec3 _value, int _handler);
    void SendBool(bool _value, int _handler);
};
