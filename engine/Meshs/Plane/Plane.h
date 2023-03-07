#pragma once

#include "engine/Meshs/Mesh/Mesh.h"

class Plane : public Mesh
{
protected:
    int mNbVertexWidth = 0;
    int mNbVertexLength = 0;

public: 
    Plane(const int _nbVertexWidth, const int _nbVertexLength);

protected:
    void CreatePlane(const bool& _generatePos = true, const bool& _generateUV = true, const bool& _generateIndices = true);
    virtual void CreateVerticesPositions() override;
    virtual void CreateVerticesUVs() override;
    virtual void CreateIndices() override;
};