#include "LandscapeMaterial.h"
#include "engine/Landscape/ShaderHandler/LandscapeShaderHandler.h"
#include "engine/FilesPath/FilesPath.h"

LandscapeMaterial::LandscapeMaterial()
{
    mShaderHandler = new LandscapeShaderHandler(LANDSCAPE_VERTEX, LANDSCAPE_FRAG);
    mShaderHandler->Initialize();
    mShader = mShaderHandler;
}

LandscapeMaterial::LandscapeMaterial(const string& _vertexShader, const string& _fragShader)
{
    mShaderHandler = new LandscapeShaderHandler(_vertexShader, _fragShader);
    mShaderHandler->Initialize();
    mShader = mShaderHandler;
}

void LandscapeMaterial::UseMaterial(const mat4& _model, const mat4& _view, const mat4& _proj)
{
    BaseMaterial::UseMaterial(_model, _view, _proj);

    //Send heightmap
    mShaderHandler->SendTexture(GL_TEXTURE_2D, 0, mHeightmap, mShaderHandler->GetHeightmapHandler());

    //Send height
    mShaderHandler->SendFloat(mHeight, mShaderHandler->GetHeightHandler());
    mShaderHandler->SendFloat(mShift, mShaderHandler->GetShiftHandler());

    //Send layers
    unsigned int _nbLayers = mLayers.size();
    for(int _layerSlot = 0; _layerSlot<_nbLayers; ++_layerSlot)
        mShaderHandler->SendTexture(GL_TEXTURE_2D, _layerSlot+1, mLayers[_layerSlot], mShaderHandler->GetLayersHandlers()[_layerSlot]);

    //Send layers transitions height
    unsigned int _nbTransition = mHeightsTransition.size();
    for(int _transitionSlot = 0; _transitionSlot<_nbTransition; ++_transitionSlot)
        mShaderHandler->SendFloat(mHeightsTransition[_transitionSlot], mShaderHandler->GetHeightsTransitionHandlers()[_transitionSlot]);

    //Send transitions threshold
    mShaderHandler->SendFloat(mTransitionThreshold, mShaderHandler->GetTransitionThresholdHandler());

    //Send tiling
    mShaderHandler->SendInt(mTiling, mShaderHandler->GetTilingHandler());
}