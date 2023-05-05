#pragma once

#include <glm/glm.hpp>
using namespace glm;

#include <string>
using namespace std;

#include "engine/Utils/TextureLoader/TextureLoader.h"

class BaseShaderHandler;

class BaseMaterial
{
protected:
    BaseShaderHandler* mShader = nullptr;

public:
    BaseShaderHandler* GetShader() const {return mShader;}
    void SetShader(BaseShaderHandler* const _shader){mShader = _shader;}

public:
    virtual void DeleteTexture(unsigned int& _texture);

    virtual void UseMaterial(const mat4& _model, const mat4& _view, const mat4& _proj);

    void LoadTexture(unsigned int& _textureSlot, const string& _texturePath);
};