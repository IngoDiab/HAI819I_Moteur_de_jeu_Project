#pragma once
#include<string>
#include <vector>
#include <map>
using namespace std;

#include <glm/glm.hpp>
using namespace glm;

#include "engine/ShaderHandlers/BaseShaderHandler/BaseShaderHandler.h"

class ShaderHandler : public BaseShaderHandler
{
protected:
    int mIsUsingNormalMapHandler = false;
    vector<int> mColorsHandlers = vector<int>(3);
    vector<int> mTexturesHandlers = vector<int>(7);
    vector<int> mCoeffsHandlers = vector<int>(7);

public:
    int GetIsUsingNormalMapHandler(){return mIsUsingNormalMapHandler;}
    vector<int> GetColorHandlers() const {return mColorsHandlers;}
    vector<int> GetTexturesHandlers() const {return mTexturesHandlers;}
    vector<int> GetCoeffsHandlers() const {return mCoeffsHandlers;}

public:
    ShaderHandler(const string& _vertexShader, const string& _fragShader);

public:
    unsigned int GetShaderHandler() const {return mShaderHandler;}

public:
    virtual void Initialize();
};
