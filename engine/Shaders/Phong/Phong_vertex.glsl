#version 330 core

layout(location = 0) in vec3 vertices_position_modelspace;
layout(location = 1) in vec2 vertices_uv_modelspace;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 o_uv;
out vec3 o_pos;

void main()
{
        gl_Position = projection * view * model * vec4(vertices_position_modelspace,1);
        o_uv = vertices_uv_modelspace;
        o_pos = (model * vec4(vertices_position_modelspace,1)).xyz;
}

