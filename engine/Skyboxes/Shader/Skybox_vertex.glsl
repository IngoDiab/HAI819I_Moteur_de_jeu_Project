#version 330 core

layout(location = 0) in vec3 position;

out vec3 o_position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main() 
{
  o_position = position;
  gl_Position = projection * view * vec4(position, 1.0);
}