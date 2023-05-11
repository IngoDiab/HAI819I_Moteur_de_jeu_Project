#pragma once

#include <glm/glm.hpp>
using namespace glm;

#include <string>
using namespace std;

#include "engine/Objects/GameObject/GameObject.h"

class DirectionalLight : public GameObject
{
protected:
	vec3 mColor = vec3(1);
    vec3 mDirection = vec3(0,-1,0);
	bool mIsEnabled = true;

public:
	vec3 GetColor() const { return mColor; }
	void SetColor(const vec3& _color) { mColor = _color;}

	vec3 GetDirection() const {return mDirection;}
	void SetDirection(const vec3& _direction) { mDirection = _direction;}

	bool IsEnabled(){return mIsEnabled;}
	void Enable(bool _enable){mIsEnabled = _enable;}

public:
    DirectionalLight();
    DirectionalLight(const vec3& _color, const vec3& _direction);

public:
    virtual ~DirectionalLight();
	virtual void Destroy() override;
};