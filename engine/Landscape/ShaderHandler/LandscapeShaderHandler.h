#pragma once
#include "engine/ShaderHandlers/BaseShaderHandler/BaseShaderHandler.h"

class LandscapeShaderHandler final : public BaseShaderHandler
{
protected:
    int mHeightmapHandler;
    int mHeightHandler;
    int mShifttHandler;

    vector<int> mLayersHandlers = vector<int>(15);
    vector<int> mHeightsTransitionHandlers = vector<int>(14);
    int mTransitionThresholdHandler;

    int mTilingHandler;

public:
    int GetHeightmapHandler() const {return mHeightmapHandler;}
    int GetHeightHandler() const {return mHeightHandler;}
    int GetShiftHandler() const {return mShifttHandler;}
    vector<int> GetLayersHandlers() const {return mLayersHandlers;}
    vector<int> GetHeightsTransitionHandlers() const {return mHeightsTransitionHandlers;}
    int GetTransitionThresholdHandler() const {return mTransitionThresholdHandler;}
    int GetTilingHandler() const {return mTilingHandler;}

public:
    LandscapeShaderHandler(const string& _vertexShader, const string& _fragShader);

public:
    virtual void Initialize() override;

public:
    void SendHeightmap(unsigned int _heightMap);
};
