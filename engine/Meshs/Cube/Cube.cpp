#include "Cube.h"

Cube::Cube() : Mesh()
{
    CreateCube();
}

void Cube::CreateCube(const bool& _generatePos, const bool& _generateUV, const bool& _generateIndices)
{
    if(_generatePos)
    {
        CreateVerticesPositions();
        RefreshVBOData(VERTEX_ATTRIBUTE::VERTEX_POSITION);
    }

    if(_generateUV)
    {
        CreateVerticesUVs();
        RefreshVBOData(VERTEX_ATTRIBUTE::VERTEX_UVS);
    }

    if(_generateIndices)
    {
        CreateIndices();
        RefreshVBOData(VERTEX_ATTRIBUTE::VERTEX_INDICES);
    }
}

void Cube::CreateVerticesPositions()
{
    mPositions.clear();
    mPositions = 
    {
        #pragma region Face Bottom
        vec3(-0.5,-0.5,-0.5), //LeftBotFar
        vec3(0.5,-0.5,-0.5), //RightBotFar
        vec3(-0.5,-0.5,0.5), //LeftBotNear
        vec3(0.5,-0.5,0.5), //RightBotNear
        #pragma endregion

        #pragma region Face Top
        vec3(0.5,0.5,-0.5), //RightTopFar
        vec3(-0.5,0.5,-0.5), //LeftTopFar
        vec3(0.5,0.5,0.5), //RightTopNear
        vec3(-0.5,0.5,0.5), //LeftTopNear
        #pragma endregion

        #pragma region Face Front
        vec3(-0.5,-0.5,0.5), //LeftBotNear
        vec3(0.5,-0.5,0.5), //RightBotNear
        vec3(-0.5,0.5,0.5), //LeftTopNear
        vec3(0.5,0.5,0.5), //RightTopNear
        #pragma endregion

        #pragma region Face Back
        vec3(0.5,0.5,-0.5), //RightTopFar
        vec3(-0.5,-0.5,-0.5), //LeftBotFar
        vec3(-0.5,0.5,-0.5), //LeftTopFar
        vec3(0.5,-0.5,-0.5), //RightBotFar
        #pragma endregion

        #pragma region Face Right
        vec3(0.5,0.5,-0.5), //RightTopFar
        vec3(0.5,-0.5,0.5), //RightBotNear
        vec3(0.5,-0.5,-0.5), //RightBotFar
        vec3(0.5,0.5,0.5), //RightTopNear
        #pragma endregion

        #pragma region Face Left
        vec3(-0.5,0.5,-0.5), //LeftTopFar
        vec3(-0.5,-0.5,-0.5), //LeftBotFar
        vec3(-0.5,-0.5,0.5), //LeftBotNear
        vec3(-0.5,0.5,0.5), //LeftTopNear
        #pragma endregion
    };
}

void Cube::CreateVerticesUVs()
{
    mUVs.clear();
    mUVs = 
    {
        #pragma region Face Bottom
        vec2(0,0), //LeftBotFar
        vec2(0.5,0), //RightBotFar
        vec2(0,0.5), //LeftBotNear
        vec2(0.5,0.5), //RightBotNear
        #pragma endregion

        #pragma region Face Top
        vec2(0.5,0.5), //RightTopFar
        vec2(0,0.5), //LeftTopFar
        vec2(0.5,0), //RightTopNear
        vec2(0,0), //LeftTopNear
        #pragma endregion

        #pragma region Face Front
        vec2(0,0), //LeftBotNear
        vec2(0.5,0), //RightBotNear
        vec2(0,0.5), //LeftTopNear
        vec2(0.5,0.5), //RightTopNear
        #pragma endregion

        #pragma region Face Back
        vec2(0,0.5), //RightTopFar
        vec2(0.5,0), //LeftBotFar
        vec2(0.5,0.5), //LeftTopFar
        vec2(0,0), //RightBotFar
        #pragma endregion

        #pragma region Face Right
        vec2(0.5,0.5), //RightTopFar
        vec2(0,0), //RightBotNear
        vec2(0.5,0), //RightBotFar
        vec2(0,0.5), //RightTopNear
        #pragma endregion

        #pragma region Face Left
        vec2(0.5,0.5), //LeftTopFar
        vec2(0.5,0), //LeftBotFar
        vec2(0,0), //LeftBotNear
        vec2(0,0.5) //LeftTopNear
        #pragma endregion
    };
    
}

void Cube::CreateIndices()
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