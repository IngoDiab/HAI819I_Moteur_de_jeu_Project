#pragma once

#include "engine/Meshs/Mesh/Mesh.h"

class Sphere : public Mesh
{
    int mNbVertexAzimut = 200;
    int mNbVertexElevation = 200;

public:
    Sphere();
    
protected:
    void CreateSphere(const bool& _generatePos = true, const bool& _generateUV = true, const bool& _generateIndices = true);
    virtual void CreateVerticesPositions() override;
    virtual void CreateVerticesUVs() override;
    virtual void CreateIndices() override;

private:
    vec3 SphericalCoordinatesToEuclidean( float theta , float phi );
};