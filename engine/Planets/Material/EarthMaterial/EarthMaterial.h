#pragma once

#include "engine/Materials/Material.h"

#include <string>
using namespace std;

#define EARTH_VERTEX "Shaders/Phong/Phong_vertex.glsl"
#define EARTH_FRAG "Shaders/Phong/Phong_frag.glsl"

class EarthMaterial : public Material
{
public:
    EarthMaterial();
    EarthMaterial(const string& _vertexShader, const string& _fragShader);

public:
    virtual void Initialize() override;
};