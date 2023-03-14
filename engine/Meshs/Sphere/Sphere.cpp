#include "Sphere.h"

Sphere::Sphere() : Mesh()
{
    CreateSphere();
}

void Sphere::CreateSphere(const bool& _generatePos, const bool& _generateUV, const bool& _generateIndices)
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

vec3 Sphere::SphericalCoordinatesToEuclidean(const float _azimut , const float _elevation) {
    return vec3(cos(_azimut) * cos(_elevation), sin(_elevation), sin(_azimut) * cos(_elevation));
}

void Sphere::CreateVerticesPositions()
{
    float _stepAzimut = 2*M_PI/(float)(mNbVertexAzimut-1);
    float _stepElevation = M_PI/(float)(mNbVertexElevation-1);

    mPositions.clear();
    mPositions.resize(mNbVertexAzimut * mNbVertexElevation);
    
    for(int _azimutIndex = 0; _azimutIndex < mNbVertexAzimut; ++_azimutIndex)
        for(int _elevationIndex = 0; _elevationIndex < mNbVertexElevation; ++_elevationIndex)
            mPositions[_azimutIndex * mNbVertexElevation + _elevationIndex] = SphericalCoordinatesToEuclidean(_azimutIndex * _stepAzimut, -(_elevationIndex -(mNbVertexElevation-1)/2.)  * _stepElevation);
}

void Sphere::CreateVerticesUVs()
{
    mUVs.clear();
    mUVs.resize(mNbVertexAzimut * mNbVertexElevation);
    
    for(int _azimutIndex = 0; _azimutIndex < mNbVertexAzimut; ++_azimutIndex)
        for(int _elevationIndex = 0; _elevationIndex < mNbVertexElevation; ++_elevationIndex)
            mUVs[_azimutIndex * mNbVertexElevation + _elevationIndex] = vec2(_azimutIndex/(float)(mNbVertexAzimut-1), _elevationIndex/(float)(mNbVertexElevation-1));
}

void Sphere::CreateIndices()
{
    mIndices.clear();
    
    for(int _azimutIndex = 0; _azimutIndex < mNbVertexAzimut; ++_azimutIndex)
        for(int _elevationIndex = 0; _elevationIndex < mNbVertexElevation-1; ++_elevationIndex)
        {
            int _nextOnAzimut = _azimutIndex+1 >= mNbVertexAzimut ? 0 : _azimutIndex+1;
            mIndices.push_back(_azimutIndex*mNbVertexElevation + _elevationIndex);
            mIndices.push_back(_nextOnAzimut*mNbVertexElevation + _elevationIndex+1);
            mIndices.push_back(_azimutIndex*mNbVertexElevation + _elevationIndex+1);

            mIndices.push_back(_azimutIndex*mNbVertexElevation + _elevationIndex);
            mIndices.push_back(_nextOnAzimut*mNbVertexElevation + _elevationIndex);
            mIndices.push_back(_nextOnAzimut*mNbVertexElevation + _elevationIndex+1);
        }
}