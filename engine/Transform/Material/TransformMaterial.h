#pragma once
#include "engine/Materials/Material.h"

#include <string>
using namespace std;

class TransformMaterial : public Material
{

public:
    TransformMaterial();
    TransformMaterial(const string& _vertexShader, const string& _fragShader);

public:
    virtual void Initialize() override;
};