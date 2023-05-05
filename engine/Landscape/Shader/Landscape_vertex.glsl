#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 uv;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform int mTiling;
uniform float mHeight;
uniform float mShift;
uniform sampler2D mHeightmap;

out vec2 o_uv;
out float o_height_in_model;

void main()
{
        float _heightTexel = texture(mHeightmap, uv).r;
        vec3 position_heightmap_applied = position + vec3(0,1,0)*_heightTexel*mHeight - vec3(0,1,0)*mShift;
        gl_Position = projection * view * model * vec4(position_heightmap_applied,1);
        o_uv = uv*mTiling;
        o_height_in_model = position_heightmap_applied.y;
}

