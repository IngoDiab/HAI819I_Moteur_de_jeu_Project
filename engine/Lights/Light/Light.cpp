#include "Light.h"

Light::~Light()
{
    
}

Light::Light() : GameObject()
{

}

Light::Light(const vec3& _positions) : GameObject(_positions,vec3(0,0,0),vec3(1,1,1))
{

}

Light::Light(const vec3& _positions, const vec3& _rotations, const vec3& _scale) : GameObject(_positions,_rotations,_scale)
{

}