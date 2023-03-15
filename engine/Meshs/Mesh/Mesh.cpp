#include "Mesh.h"

#define GL_ARRAY_BUFFER 0x8892
#define GL_ELEMENT_ARRAY_BUFFER 0x8893
#define GL_FLOAT 0x1406
#define GL_TRIANGLES 0x0004

Mesh::Mesh()
{

}

Mesh::~Mesh()
{
    
}

Mesh::Mesh(const vector<vec3>& _positions, const vector<vec2>& _uvs, const vector<unsigned short>& _indices, const std::vector<Triangle>& _triangles) : mPositions(_positions), mUVs(_uvs), mIndices(_indices), mTriangles(_triangles)
{
    RefreshVBOData(VERTEX_ATTRIBUTE::VERTEX_POSITION);
    RefreshVBOData(VERTEX_ATTRIBUTE::VERTEX_UVS);
    RefreshVBOData(VERTEX_ATTRIBUTE::VERTEX_INDICES);
}

void Mesh::RefreshVBOData(const VERTEX_ATTRIBUTE _vbo)
{
    switch (_vbo)
    {
    case VERTEX_ATTRIBUTE::VERTEX_POSITION:
        mPositionVBO.CopyDataToVBO(mPositions);
        break;

    case VERTEX_ATTRIBUTE::VERTEX_UVS:
        mUVsVBO.CopyDataToVBO(mUVs);
        break;

    case VERTEX_ATTRIBUTE::VERTEX_INDICES:
        mIndicesVBO.CopyDataToVBO(mIndices);
        break;
    
    default:
        break;
    }
}

void Mesh::DrawMesh()
{
    mPositionVBO.DrawVBO(0, 3, GL_FLOAT);
    mUVsVBO.DrawVBO(1, 2, GL_FLOAT);
    mIndicesVBO.DrawVBOIndices(GL_TRIANGLES, mIndices.size());
}