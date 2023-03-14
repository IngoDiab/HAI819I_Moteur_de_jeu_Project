#pragma once

#include "engine/Materials/Material.h"

#include <string>
using namespace std;

#define SUN_VERTEX "Shaders/Phong/Phong_vertex.glsl"
#define SUN_FRAG "Shaders/Phong/Phong_frag.glsl"

class SunMaterial : public Material
{
public:
    SunMaterial();
    SunMaterial(const string& _vertexShader, const string& _fragShader);

public:
    virtual void Initialize() override;
};