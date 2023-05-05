#include "LandscapeShaderHandler.h"
#include <GL/glew.h>

LandscapeShaderHandler::LandscapeShaderHandler(const string& _vertexShader, const string& _fragShader) : BaseShaderHandler(_vertexShader,_fragShader)
{

}

void LandscapeShaderHandler::Initialize()
{
    BaseShaderHandler::Initialize();

    //Get heightmap handler
    GetTextureLocation(mHeightmapHandler, "mHeightmap");

    //Get height handler
    GetUniformLocation(mHeightHandler, "mHeight");
    GetUniformLocation(mShifttHandler, "mShift");

    //Get layers handler
    unsigned int _nbLayers = mLayersHandlers.size();
    for(unsigned int _layerSlot = 0; _layerSlot<_nbLayers; ++_layerSlot)
        GetTextureLocation(mLayersHandlers[_layerSlot], "mLayer"+to_string(_layerSlot));

    //Get transitions handler
    unsigned int _nbTransition = mHeightsTransitionHandlers.size();
    for(unsigned int _layerTransition = 0; _layerTransition<_nbTransition; ++_layerTransition)
        GetUniformLocation(mHeightsTransitionHandlers[_layerTransition], "mTransition"+to_string(_layerTransition)+"_"+to_string(_layerTransition+1));

    //Get TransitionThreshold handler
    GetUniformLocation(mTransitionThresholdHandler, "mTransitionThreshold");

    //Get tiling handler
    GetUniformLocation(mTilingHandler, "mTiling");
}

void LandscapeShaderHandler::SendHeightmap(unsigned int _heightMap)
{

}