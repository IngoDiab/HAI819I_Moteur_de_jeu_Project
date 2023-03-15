#pragma once

#include <glm/glm.hpp>
using namespace glm;

#include <string>
using namespace std;

#include "engine/Utils/TextureLoader/TextureLoader.h"

class ShaderHandler;

class Material
{
protected:
    ShaderHandler* mShader = nullptr;
    vector<unsigned int> mTextures = vector<unsigned int>(16);

public:
    ShaderHandler* GetShader() const {return mShader;}
    void SetShader(ShaderHandler* const _shader){mShader = _shader;}

public:
    virtual ~Material();

public:
    virtual void Initialize() = 0;
    virtual void DeleteTexture(unsigned int& _texture);

    virtual void UseMaterial(const int _typeTexture, const mat4& _model, const mat4& _view, const mat4& _proj);
    virtual void LoadTexture(const int _textureSlot, const string& _texturePath);
    virtual void LoadCubemapTexture(const int _textureSlot, const vector<string>& _texturePaths);
};