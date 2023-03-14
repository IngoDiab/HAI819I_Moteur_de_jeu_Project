#version 330 core

layout(location = 0) in vec3 vertices_position_modelspace;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 o_position_model;

void main()
{
        gl_Position = projection * view * model * vec4(vertices_position_modelspace,1);
        o_position_model = vertices_position_modelspace;
}

