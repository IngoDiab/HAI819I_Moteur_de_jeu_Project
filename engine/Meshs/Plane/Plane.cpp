#include "Plane.h"

Plane::Plane(const int _nbVertexWidth, const int _nbVertexLength) : mNbVertexWidth(_nbVertexWidth), mNbVertexLength(_nbVertexLength)
{
    CreatePlane();
}

void Plane::CreatePlane(const bool& _generatePos, const bool& _generateUV, const bool& _generateIndices)
{
    if(_generatePos)
    {
        CreateVerticesPositions();
        RefreshVBOData(VERTEX_ATTRIBUTE::VERTEX_POSITION);
    }

    if(_generateUV)
    {
        CreateVerticesUVs();
        RefreshVBOData(VERTEX_ATTRIBUTE::VERTEX_UVS);
    }

    if(_generateIndices)
    {
        CreateIndices();
        RefreshVBOData(VERTEX_ATTRIBUTE::VERTEX_INDICES);
    }
}

void Plane::CreateVerticesPositions()
{
    mPositions.clear();
    for(int i = 0; i < mNbVertexLength; ++i)
        for(int j = 0; j < mNbVertexWidth; ++j)
            mPositions.push_back(vec3(j/(float)(mNbVertexWidth-1)-.5f,0,i/(float)(mNbVertexLength-1)-.5f));
}

void Plane::CreateVerticesUVs()
{
    mUVs.clear();
    for(int i = 0; i < mNbVertexLength; ++i)
        for(int j = 0; j < mNbVertexWidth; ++j)
            mUVs.push_back(vec2(j/(float)mNbVertexWidth,i/(float)mNbVertexLength));
}

void Plane::CreateIndices()
{
    mIndices.clear();
    for(int i = 0; i < mNbVertexLength-1; ++i)
        for(int j = 0; j < mNbVertexWidth-1; ++j)
        {
            //first triangle
            mIndices.push_back(i*mNbVertexWidth+j);
            mIndices.push_back((i+1)*mNbVertexWidth+j);
            mIndices.push_back((i+1)*mNbVertexWidth+j+1);
            //seconde triangle
            mIndices.push_back(i*mNbVertexWidth+j);
            mIndices.push_back((i+1)*mNbVertexWidth+j+1);
            mIndices.push_back(i*mNbVertexWidth+j+1);
        }
}