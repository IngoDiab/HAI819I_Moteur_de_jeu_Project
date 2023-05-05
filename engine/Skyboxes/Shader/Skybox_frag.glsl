#version 330 core

in vec3 o_position;

out vec4 FragColor;

uniform samplerCube mCubemap;

void main() 
{
    FragColor = texture(mCubemap, o_position);
}