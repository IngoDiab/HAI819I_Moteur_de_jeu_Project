#pragma once

#include <glm/glm.hpp>
using namespace glm;

#include <string>
using namespace std;

#include "engine/Objects/GameObject/GameObject.h"

class Light : public GameObject
{
protected:
	vec3 mColor;
	float mIntensity;
	bool mEnabled;

public:
	vec3 GetColor() { return mColor; }
	void SetColor(vec3 _color) { mColor = _color;}

	float GetIntensity() {return mIntensity;}
	void SetIntensity(float _intensity) { mIntensity = _intensity;}

	bool GetEnabled(){return mEnabled;}
	void SetEnabled(bool _enabled){mEnabled = _enabled;}

public:
    virtual ~Light();

public:
    Light();
    Light(const vec3& _positions);
    Light(const vec3& _positions, const vec3& _rotations, const vec3& _scale);
};