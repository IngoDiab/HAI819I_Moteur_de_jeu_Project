#pragma once

#include "engine/Materials/Material.h"

#include <string>
using namespace std;

#define MOON_VERTEX "Shaders/Phong/Phong_vertex.glsl"
#define MOON_FRAG "Shaders/Phong/Phong_frag.glsl"

class MoonMaterial : public Material
{
public:
    MoonMaterial();
    MoonMaterial(const string& _vertexShader, const string& _fragShader);

public:
    virtual void Initialize() override;
};