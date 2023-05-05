#pragma once

#include <glm/glm.hpp>
using namespace glm;

#include <string>
using namespace std;

#include "engine/FilesPath/FilesPath.h"
#include "engine/Materials/BaseMaterial/BaseMaterial.h"

enum class COLOR_SLOT
{
    AMBIENT = 0,
    DIFFUSE = 1,
    SPECULAR = 2
};

enum class TEXTURE_SLOT
{
    ALBEDO = 0,
    NORMAL_MAP = 1,
    METALLIC_MAP = 2,
    ROUGH_MAP = 3,
    OCCLUSION_MAP = 4,
    EMISSIVE_MAP = 5,
    HEIGHTMAP = 6
};

enum class COEFF_SLOT
{
    METALNESS = 0,
    ROUGHNESS = 1,
    OCCLUSIONESS = 2,
    EMISSIVNESS = 3,
    HEIGHT = 4,
    TILING = 5,
    SHININESS = 6
};

class ShaderHandler;

class Material : public BaseMaterial
{
protected:
    ShaderHandler* mShaderHandler = nullptr;

    bool mIsUsingNormalMap = false;
    vector<vec3> mColors = vector<vec3>(3);
    vector<unsigned int> mTextures = vector<unsigned int>(7);
    vector<float> mCoeffs = vector<float>(7);

public:
    void SetTexture(const TEXTURE_SLOT _slot, const string& _texturePath){LoadTexture(mTextures[(int)_slot], _texturePath);}
    void SetValueCoefficients(COEFF_SLOT _slot, int _value) {mCoeffs[(int)_slot] = _value;}

public:
    Material();
    Material(const string& _vertexShader, const string& _fragShader);
    virtual ~Material();

public:
    virtual void Initialize();

    virtual void UseMaterial(const mat4& _model, const mat4& _view, const mat4& _proj);
};