#version 330 core

uniform sampler2D mGrassTex;
uniform float mHeightGrassRock;
uniform sampler2D mRockTex;
uniform float mHeightRockSnow;
uniform sampler2D mSnowrockTex;

uniform float mTransitionThreshold;

in vec3 o_position;
in vec2 o_uv;
in float o_height_in_model;

out vec4 FragColor;

void main(){
        vec4 _texelGrass = texture(mGrassTex, o_uv);
        vec4 _texelRock = texture(mRockTex, o_uv);
        vec4 _texelSnowrock = texture(mSnowrockTex, o_uv);

        float mHeightGrassRockMin = mHeightGrassRock - mTransitionThreshold;
        float mHeightGrassRockMax = mHeightGrassRock + mTransitionThreshold;

        float mHeightRockSnowMin = mHeightRockSnow - mTransitionThreshold;
        float mHeightRockSnowMax = mHeightRockSnow + mTransitionThreshold;

        //Grass
        if(o_height_in_model<=mHeightGrassRockMin) FragColor = _texelGrass;
        else if(o_height_in_model<=mHeightGrassRockMax) FragColor = mix(_texelGrass, _texelRock, (o_height_in_model- mHeightGrassRockMin)/(mHeightGrassRockMax - mHeightGrassRockMin));

        //Rock
        else if(o_height_in_model<=mHeightRockSnowMin) FragColor = _texelRock;
        else if(o_height_in_model<=mHeightRockSnowMax) FragColor = mix(_texelRock, _texelSnowrock, (o_height_in_model-mHeightRockSnowMin)/(mHeightRockSnowMax-mHeightRockSnowMin));

        //Snow
        else if(o_height_in_model>mHeightRockSnowMax) FragColor = _texelSnowrock;
}