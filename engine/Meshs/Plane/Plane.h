#pragma once

#include "engine/Meshs/Mesh/Mesh.h"

class Plane : public Mesh
{
protected:
    int mNbVertexWidth = 0;
    int mNbVertexLength = 0;

public: 
    Plane();
    Plane(const int _nbVertexWidth, const int _nbVertexLength);

public:
    vec3 GetPositonVertex(const float _u, const float _v, bool _ceilU, bool _ceilV);
    vec2 GetUVVertex(const float _u, const float _v, bool _ceilU, bool _ceilV);

protected:
    void CreatePlane(const bool _generatePos = true, const bool _generateUV = true, const bool _generateIndices = true, const bool _generateNormales = true);
    virtual void CreateVerticesPositions() override;
    virtual void CreateVerticesUVs() override;
    virtual void CreateIndices() override;
    virtual void CreateVerticesNormales() override;
};