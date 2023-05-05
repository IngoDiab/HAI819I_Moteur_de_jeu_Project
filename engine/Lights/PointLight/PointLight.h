#pragma once

#include <glm/glm.hpp>
using namespace glm;

#include <string>
using namespace std;

#include "engine/Objects/GameObject/GameObject.h"

class PointLight : public GameObject
{
protected:
	vec3 mColor = vec3(1);
	float mIntensity = 10;
	bool mIsEnabled = true;

public:
	vec3 GetColor() { return mColor; }
	void SetColor(vec3 _color) { mColor = _color;}

	float GetIntensity() {return mIntensity;}
	void SetIntensity(float _intensity) { mIntensity = _intensity;}

	bool IsEnabled(){return mIsEnabled;}
	void Enable(bool _enable){mIsEnabled = _enable;}

public:
    PointLight();
    PointLight(const vec3& _positions);
    PointLight(const vec3& _positions, const vec3& _rotations, const vec3& _scale);

public:
    virtual ~PointLight();
};