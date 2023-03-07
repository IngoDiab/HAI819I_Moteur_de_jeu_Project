#pragma once

#include <vector>
using namespace std;

#include <glm/glm.hpp>
using namespace glm;

#include "engine/Buffers/VBO/VBO.h"

enum class VERTEX_ATTRIBUTE
{
    VERTEX_POSITION = 0,
    VERTEX_UVS = 1,
    VERTEX_INDICES = 2,
    //VERTEX_TRIANGLES = 3 //(?)
};

struct Triangle
{
    vector<unsigned int> mIndices = vector<unsigned int>(3);

    Triangle(const vector<unsigned int>& _indices) : mIndices(_indices){}
    Triangle(const unsigned int _indice0, const unsigned int _indice1, const unsigned int _indice2)
    {
        mIndices[0] = _indice0;
        mIndices[1] = _indice1;
        mIndices[2] = _indice2;
    }

    unsigned int operator[](const int _index) { return mIndices[_index]; }
};

class Mesh
{
protected:
    vector<vec3> mPositions = vector<vec3>();
    VBO mPositionVBO = VBO(GL_ARRAY_BUFFER);

    vector<vec2> mUVs = vector<vec2>();
    VBO mUVsVBO = VBO(GL_ARRAY_BUFFER);

    vector<unsigned short> mIndices = vector<unsigned short>();
    VBO mIndicesVBO = VBO(GL_ELEMENT_ARRAY_BUFFER);

    std::vector<Triangle> mTriangles;

public:
    Mesh();
    Mesh(const vector<vec3>& _positions, const vector<vec2>& _uvs, const vector<unsigned short>& _indices, const std::vector<Triangle>& _triangles);

protected:
    void RefreshVBOData(const VERTEX_ATTRIBUTE _vbo);

    virtual void CreateVerticesPositions() = 0;
    virtual void CreateVerticesUVs() = 0;
    virtual void CreateIndices() = 0;

public:
    virtual void DrawMesh();
};