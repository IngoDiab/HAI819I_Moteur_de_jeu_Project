#include "SkyboxMesh.h"

SkyboxMesh::SkyboxMesh(): Cube()
{
    CreateSkyboxMesh();
}

void SkyboxMesh::CreateSkyboxMesh(const bool& _generateIndices)
{
    if(!_generateIndices) return;
    CreateIndices();
    RefreshVBOData(VERTEX_ATTRIBUTE::VERTEX_INDICES);
}

void SkyboxMesh::CreateIndices()
{
    mIndices.clear();
    mIndices =
    {
        #pragma region Face Bottom
        2, 1, 0,
        2, 3, 1,
        #pragma endregion

        #pragma region Face Top
        6, 5, 4,
        6, 7, 5,
        #pragma endregion

        #pragma region Face Front
        10, 9, 8,
        10, 11, 9,
        #pragma endregion

        #pragma region Face Back
        14, 13, 12,
        13, 15, 12,
        #pragma endregion

        #pragma region Face Right
        18, 17, 16,
        17, 19, 16,
        #pragma endregion

        #pragma region Face Left
        22, 21, 20,
        23, 22, 20,
        #pragma endregion
    };
}