#include "LandscapeMesh.h"

LandscapeMesh::LandscapeMesh() : Plane(16,16){}

LandscapeMesh::LandscapeMesh(const int _nbVertexWidth, const int _nbVertexLength) : Plane(ClampVertexNb(_nbVertexWidth),ClampVertexNb(_nbVertexLength)){}

void LandscapeMesh::ApplyHeightmap(const unsigned char* _heightmapImage, const float _maxHeight, const int _widthImage, const int _heightImage, const double& _gameobjectScaleY)
{
    mPositions.clear();
    float maxPosY = 0;
    for(int i = 0; i < mNbVertexLength; ++i)
        for(int j = 0; j < mNbVertexWidth; ++j)
        {
            const vec2 _uv = mUVs[i*mNbVertexWidth + j];
            const long _lineIndex = _uv.y* _heightImage;
            const long _columnIndex = _uv.x* _widthImage;
            const long _index = _lineIndex* _widthImage + _columnIndex;
            const double _texelValue = _heightmapImage[_index]/255.;
            const float _yPos = _texelValue*_maxHeight/_gameobjectScaleY; //Cancel Y scale
            maxPosY = maxPosY<_yPos ? _yPos : maxPosY;
            mPositions.push_back(vec3(i/(float)(mNbVertexWidth-1)-.5f,_yPos,j/(float)(mNbVertexLength-1)-.5f));
        }
    RefreshVBOData(VERTEX_ATTRIBUTE::VERTEX_POSITION);
}

void LandscapeMesh::ChangeResolution(const int _nbVertexWidth, const int _nbVertexLength)
{
    mNbVertexWidth = ClampVertexNb(_nbVertexWidth);
    mNbVertexLength = ClampVertexNb(_nbVertexLength);
    CreatePlane();
}

void LandscapeMesh::ChangeResolution(const int _change)
{
    mNbVertexWidth = ClampVertexNb(mNbVertexWidth+_change);
    mNbVertexLength = ClampVertexNb(mNbVertexLength+_change);
    CreatePlane();
}

int LandscapeMesh::ClampVertexNb(const int _nbVertex)
{
    return _nbVertex < 2 ? 2 : _nbVertex > 256 ? 256 : _nbVertex;
}