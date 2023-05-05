#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 uv;
layout(location = 2) in vec3 normale;
//
layout(location = 3) in vec3 tangent;
layout(location = 4) in vec3 bitangent;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


//Out
out vec2 o_uv;
out vec3 o_positionWorld;
out vec3 o_normale;

out mat3 o_TBN;

void main()
{
        vec4 positionWorld = model * vec4(position,1);
        o_positionWorld = positionWorld.xyz;
        gl_Position = projection * view * positionWorld;
        o_uv = uv;
        o_normale = normalize(mat3(transpose(inverse(model))) * normale);
}

