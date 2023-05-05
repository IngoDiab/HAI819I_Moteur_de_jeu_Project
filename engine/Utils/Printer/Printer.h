#pragma once

#include <glm/glm.hpp>
using namespace glm;

#include <string>
#include <iostream>
using namespace std;

void Print(const string& _string)
{
    cout<<_string<<endl;
}

void PrintVector(const string& _name, const vec3& _vector)
{
    cout<<_name<<" : X = "<<_vector.x<<" Y = "<<_vector.y<<" Z = "<<_vector.z<<endl;
}

void PrintVector(const vec3& _vector)
{
    cout<<"X = "<<_vector.x<<" Y = "<<_vector.y<<" Z = "<<_vector.z<<endl;
}