#pragma once

#include <string>
using namespace std;

#include "engine/Meshs/Plane/Plane.h"

class LandscapeMesh : public Plane
{

public:
    LandscapeMesh(const int _nbVertexWidth, const int _nbVertexLength);

public:
    void ApplyHeightmap(const unsigned char* _heightmapImage, const float _maxHeight, const int _widthImage, const int _heightImage, const double& _gameobjectScaleY);
    void ChangeResolution(const int _nbVertexWidth, const int _nbVertexLength);
    void ChangeResolution(const int _change);

private:
    int ClampVertexNb(const int _nbVertex);
};