#version 330 core

layout(location = 0) in vec3 vertices_position_modelspace;
layout(location = 1) in vec2 vertices_uv_modelspace;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform int mTiling;

out vec2 o_uv;
out float o_height_in_model;

void main()
{
        gl_Position = projection * view * model * vec4(vertices_position_modelspace,1);
        o_uv = vertices_uv_modelspace*mTiling;
        o_height_in_model = vertices_position_modelspace.y;
}

