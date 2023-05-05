#version 330 core

uniform sampler2D mLayer0; //Grass
uniform float mTransition0_1;
uniform sampler2D mLayer1; //Rock
uniform float mTransition1_2;
uniform sampler2D mLayer2; //Snowrocks

uniform float mTransitionThreshold;

in vec3 o_position;
in vec2 o_uv;
in float o_height_in_model;

out vec4 FragColor;

void main(){
        vec4 _texelLayer0 = texture(mLayer0, o_uv);
        vec4 _texelLayer1 = texture(mLayer1, o_uv);
        vec4 _texelLayer2 = texture(mLayer2, o_uv);

        float mHeightGrassRockMin = mTransition0_1 - mTransitionThreshold;
        float mHeightGrassRockMax = mTransition0_1 + mTransitionThreshold;

        float mHeightRockSnowMin = mTransition1_2 - mTransitionThreshold;
        float mHeightRockSnowMax = mTransition1_2 + mTransitionThreshold;

        //Layer0
        if(o_height_in_model<=mHeightGrassRockMin) FragColor = _texelLayer0;
        else if(o_height_in_model<=mHeightGrassRockMax) FragColor = mix(_texelLayer0, _texelLayer1, (o_height_in_model- mHeightGrassRockMin)/(mHeightGrassRockMax - mHeightGrassRockMin));

        //Layer1
        else if(o_height_in_model<=mHeightRockSnowMin) FragColor = _texelLayer1;
        else if(o_height_in_model<=mHeightRockSnowMax) FragColor = mix(_texelLayer1, _texelLayer2, (o_height_in_model-mHeightRockSnowMin)/(mHeightRockSnowMax-mHeightRockSnowMin));

        //layer2
        else if(o_height_in_model>mHeightRockSnowMax) FragColor = _texelLayer2;
}