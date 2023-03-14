#pragma once

#include "engine/Meshs/Mesh/Mesh.h"

class TransformMesh : public Mesh
{
public:
    TransformMesh();
    
protected:
    void CreateTransformMesh();
    virtual void CreateVerticesPositions() override;
    virtual void CreateVerticesUVs() override;
    virtual void CreateIndices() override;
};