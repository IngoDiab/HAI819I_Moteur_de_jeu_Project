#include "TransformMesh.h"

TransformMesh::TransformMesh() : Mesh()
{
    CreateTransformMesh();
}

void TransformMesh::CreateTransformMesh()
{
    CreateVerticesPositions();
    RefreshVBOData(VERTEX_ATTRIBUTE::VERTEX_POSITION);

    CreateIndices();
    RefreshVBOData(VERTEX_ATTRIBUTE::VERTEX_INDICES);
}

void TransformMesh::CreateVerticesPositions()
{
    mPositions.clear();
    mPositions = 
    {
        #pragma region Forward Vector
        vec3(0,0,0),
        vec3(0.15,0,0),
        vec3(0.15,0,1),
        vec3(0,0,1),
        #pragma endregion

        #pragma region Right Vector
        vec3(0,0,0),
        vec3(0,0,0.15),
        vec3(1,0,0.15),
        vec3(1,0,0),
        #pragma endregion

        #pragma region Up Vector
        vec3(0,0,0),
        vec3(0.15,0,0.15),
        vec3(0.15,1,0.15),
        vec3(0,1,0),
        #pragma endregion
    };
}

void TransformMesh::CreateVerticesUVs()
{
    
}

void TransformMesh::CreateIndices()
{
    mIndices.clear();
    mIndices =
    {
        #pragma region Forward Vector
        0, 1, 2,
        0, 2, 3,
        #pragma endregion

        #pragma region Right Vector
        4, 5, 6,
        4, 6, 7,
        #pragma endregion

        #pragma region Up Vector
        8, 9, 10,
        8, 10, 11,
        #pragma endregion
    };
}