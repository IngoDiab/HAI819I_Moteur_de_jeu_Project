#include "Plane.h"

Plane::Plane() : mNbVertexWidth(2), mNbVertexLength(2)
{
    CreatePlane();
}


Plane::Plane(const int _nbVertexWidth, const int _nbVertexLength) : mNbVertexWidth(_nbVertexWidth), mNbVertexLength(_nbVertexLength)
{
    CreatePlane();
}

vec3 Plane::GetPositonVertex(const float _u, const float _v, bool _ceilU, bool _ceilV)
{
    int _indexU = _ceilU ? ceil(_u*(mNbVertexWidth-1)) : floor(_u*(mNbVertexWidth-1));
    int _indexV = _ceilV ? ceil(_v*(mNbVertexLength-1)) : floor(_v*(mNbVertexLength-1));
    return mPositions[_indexV*mNbVertexWidth+_indexU];
}

vec2 Plane::GetUVVertex(const float _u, const float _v, bool _ceilU, bool _ceilV)
{
    int _indexU = _ceilU ? ceil(_u*(mNbVertexWidth-1)) : floor(_u*(mNbVertexWidth-1));
    int _indexV = _ceilV ? ceil(_v*(mNbVertexLength-1)) : floor(_v*(mNbVertexLength-1));
    return mUVs[_indexV*mNbVertexWidth+_indexU];
}

void Plane::CreatePlane(const bool _generatePos, const bool _generateUV, const bool _generateIndices, const bool _generateNormales)
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

    if(_generateNormales)
    {
        CreateVerticesNormales();
        RefreshVBOData(VERTEX_ATTRIBUTE::VERTEX_NORMALE);
    }
}

void Plane::CreateVerticesPositions()
{
    mPositions.clear();
    mPositions.resize(mNbVertexLength * mNbVertexWidth);
    for(unsigned int i = 0; i < mNbVertexLength; ++i)
        for(unsigned int j = 0; j < mNbVertexWidth; ++j)
            mPositions[i*mNbVertexWidth+j] = vec3(j/(float)(mNbVertexWidth-1)-.5f,0,i/(float)(mNbVertexLength-1)-.5f);
}

void Plane::CreateVerticesUVs()
{
    mUVs.clear();
    mUVs.resize(mNbVertexLength * mNbVertexWidth);
    for(unsigned int i = 0; i < mNbVertexLength; ++i)
        for(unsigned int j = 0; j < mNbVertexWidth; ++j)
            mUVs[i*mNbVertexWidth+j] = vec2(j/(float)mNbVertexWidth,i/(float)mNbVertexLength);
}

void Plane::CreateIndices()
{
    mIndices.clear();
    for(unsigned int i = 0; i < mNbVertexLength-1; ++i)
        for(unsigned int j = 0; j < mNbVertexWidth-1; ++j)
        {
            //first triangle
            mIndices.push_back(i*mNbVertexWidth+j);
            mIndices.push_back((i+1)*mNbVertexWidth+j+1);
            mIndices.push_back((i+1)*mNbVertexWidth+j);
            //seconde triangle
            mIndices.push_back(i*mNbVertexWidth+j);
            mIndices.push_back(i*mNbVertexWidth+j+1);
            mIndices.push_back((i+1)*mNbVertexWidth+j+1);
        }
}

void Plane::CreateVerticesNormales()
{
    mNormales.clear();
    mNormales.resize(mNbVertexLength * mNbVertexWidth);

    vector<unsigned int> _neighboors = vector<unsigned int>(mPositions.size());
    unsigned int _nbIndices = mIndices.size();
    for(int i = 0; i < _nbIndices; i+=3)
    {   
        //Get Indices
        unsigned int _index0 = mIndices[i];
        unsigned int _index1 = mIndices[i+1];
        unsigned int _index2 = mIndices[i+2];

        //Increm. neighboors
        ++_neighboors[_index0];
        ++_neighboors[_index1];
        ++_neighboors[_index2];

        //Normale triangle
        vec3 _pos0 = mPositions[_index0];
        vec3 _pos1 = mPositions[_index1];
        vec3 _pos2 = mPositions[_index2];
        vec3 _triangleNormales = normalize(cross(_pos2-_pos0, _pos1-_pos0));

        //Add normal triangle
        mNormales[_index0] += _triangleNormales;
        mNormales[_index1] += _triangleNormales;
        mNormales[_index2] += _triangleNormales;
    }

    //Get Normale per vertex
    unsigned int _nbVertex = mNormales.size();
    for(int i = 0; i < _nbVertex; ++i)
    {   
        mNormales[i] /= (float)_neighboors[i];
        mNormales[i] = normalize(mNormales[i]);
    }
}