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
        0, 1, 2,
        1, 3, 2,
        #pragma endregion

        #pragma region Face Top
        4, 5, 6,
        5, 7, 6,
        #pragma endregion

        #pragma region Face Front
        8, 9, 10,
        9, 11, 10,
        #pragma endregion

        #pragma region Face Back
        12, 13, 14,
        12, 15, 13,
        #pragma endregion

        #pragma region Face Right
        16, 17, 18,
        16, 19, 17,
        #pragma endregion

        #pragma region Face Left
        20, 21, 22,
        20, 22, 23,
        #pragma endregion
    };
}