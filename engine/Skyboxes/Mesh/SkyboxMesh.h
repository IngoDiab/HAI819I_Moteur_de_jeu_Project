#pragma once

#include "engine/Meshs/Cube/Cube.h"

class SkyboxMesh : public Cube
{
public:
    SkyboxMesh();
    
protected:
    void CreateSkyboxMesh(const bool& _generateIndices = true);
    virtual void CreateIndices() override;
};