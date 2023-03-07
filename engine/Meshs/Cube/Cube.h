#pragma once

#include "engine/Meshs/Mesh/Mesh.h"

class Cube : public Mesh
{
public:
    Cube();
    
protected:
    void CreateCube(const bool& _generatePos = true, const bool& _generateUV = true, const bool& _generateIndices = true);
    virtual void CreateVerticesPositions() override;
    virtual void CreateVerticesUVs() override;
    virtual void CreateIndices() override;
};