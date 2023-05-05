#pragma once
#include "engine/Materials/BaseMaterial/BaseMaterial.h"

#include <string>
using namespace std;

class TransformMaterial : public BaseMaterial
{

public:
    TransformMaterial();
    TransformMaterial(const string& _vertexShader, const string& _fragShader);
};