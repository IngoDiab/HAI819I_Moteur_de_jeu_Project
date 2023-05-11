#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 uv;
layout(location = 2) in vec3 normale;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform int mTiling;
uniform float mHeight;
uniform float mShift;
uniform sampler2D mHeightmap;

out vec3 o_positionWorld;
out vec2 o_uv;
out vec3 o_normale;
out float o_height_in_model;

void main()
{
        float _heightTexel = texture(mHeightmap, uv).r;
        vec3 position_heightmap_applied = position + vec3(0,1,0)*_heightTexel*mHeight - vec3(0,1,0)*mShift;
        o_positionWorld = (model * vec4(position_heightmap_applied,1)).xyz;
        gl_Position = projection * view * vec4(o_positionWorld,1.0);
        o_uv = uv*mTiling;
        o_normale = normale;
        o_height_in_model = position_heightmap_applied.y;
}

