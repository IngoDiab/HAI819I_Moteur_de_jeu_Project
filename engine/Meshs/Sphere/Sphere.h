#pragma once

#include "engine/Meshs/Mesh/Mesh.h"

class Sphere : public Mesh
{
    int mNbVertexAzimut = 200;
    int mNbVertexElevation = 200;

public:
    Sphere();
    Sphere(const bool _generatePos, const bool _generateUV, const bool _generateIndices, const bool _generateNormales);
    Sphere(const int _nbVertexAzimut, const int _nbVertexElevation);
    
protected:
    void CreateSphere(const bool _generatePos = true, const bool _generateUV = true, const bool _generateIndices = true, const bool _generateNormales = true);
    virtual void CreateVerticesPositions() override;
    virtual void CreateVerticesUVs() override;
    virtual void CreateIndices() override;
    virtual void CreateVerticesNormales() override;

private:
    vec3 SphericalCoordinatesToEuclidean( float theta , float phi );
};