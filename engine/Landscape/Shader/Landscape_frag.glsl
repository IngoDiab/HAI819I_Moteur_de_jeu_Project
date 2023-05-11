#version 330 core

uniform sampler2D mLayer0; //Grass
uniform float mTransition0_1;
uniform sampler2D mLayer1; //Rock
uniform float mTransition1_2;
uniform sampler2D mLayer2; //Snowrocks

uniform float mTransitionThreshold;

in vec3 o_positionWorld;
in vec2 o_uv;
in vec3 o_normale;
in float o_height_in_model;

uniform vec3 cameraPosition;

struct PointLight
{
    vec3 mLightPos;
    vec3 mLightColor;
    float mLightPower;
    bool mIsEnabled;
};
#define NB_POINT_LIGHTS 16
uniform PointLight mPointLights[NB_POINT_LIGHTS];

struct DirectionalLight
{
    vec3 mLightColor;
    vec3 mLightDirection;
    bool mIsEnabled;
};
uniform DirectionalLight mDirectionalLights[NB_POINT_LIGHTS];

out vec4 FragColor;

vec3 Phong(PointLight _pointLight, vec3 _normal, vec3 _albedoColor)
{
    vec3 _lightColor = _pointLight.mLightPower*_pointLight.mLightColor/(length(_pointLight.mLightPos - o_positionWorld)*length(_pointLight.mLightPos - o_positionWorld));

    vec3 _lightDirection = normalize(_pointLight.mLightPos - o_positionWorld);
    float _clampedDotDiffuse = max(dot(_lightDirection, _normal), 0.0);
    vec3 _diffuse = _albedoColor * _clampedDotDiffuse * _lightColor;

    return _diffuse;
}

vec3 Phong(DirectionalLight _dirLight, vec3 _normal, vec3 _albedoColor)
{
    vec3 _lightDirection = normalize(-_dirLight.mLightDirection);
    float _clampedDotDiffuse = max(dot(_lightDirection, _normal), 0.0);
    vec3 _diffuse = _albedoColor * _clampedDotDiffuse * _dirLight.mLightColor;

    return _diffuse;
}

void main(){
        vec3 _texelLayer0 = texture(mLayer0, o_uv).rgb;
        vec3 _texelLayer1 = texture(mLayer1, o_uv).rgb;
        vec3 _texelLayer2 = texture(mLayer2, o_uv).rgb;

        float mHeightGrassRockMin = mTransition0_1 - mTransitionThreshold;
        float mHeightGrassRockMax = mTransition0_1 + mTransitionThreshold;

        float mHeightRockSnowMin = mTransition1_2 - mTransitionThreshold;
        float mHeightRockSnowMax = mTransition1_2 + mTransitionThreshold;

        vec3 _albedoColor = vec3(0);

        //Layer0
        if(o_height_in_model<=mHeightGrassRockMin) _albedoColor = _texelLayer0;
        else if(o_height_in_model<=mHeightGrassRockMax) _albedoColor = mix(_texelLayer0, _texelLayer1, (o_height_in_model- mHeightGrassRockMin)/(mHeightGrassRockMax - mHeightGrassRockMin));

        //Layer1
        else if(o_height_in_model<=mHeightRockSnowMin) _albedoColor = _texelLayer1;
        else if(o_height_in_model<=mHeightRockSnowMax) _albedoColor = mix(_texelLayer1, _texelLayer2, (o_height_in_model-mHeightRockSnowMin)/(mHeightRockSnowMax-mHeightRockSnowMin));

        //layer2
        else if(o_height_in_model>mHeightRockSnowMax) _albedoColor = _texelLayer2;


        vec3 _ambient = 0.25 * _albedoColor;

        vec3 _resultPhong = vec3(0,0,0);
        for(int _indexLight = 0; _indexLight<NB_POINT_LIGHTS; ++_indexLight)
        {
                PointLight _pointLight = mPointLights[_indexLight];
                if(_pointLight.mIsEnabled) _resultPhong += Phong(_pointLight, o_normale, _albedoColor);

                DirectionalLight _directionalLight = mDirectionalLights[_indexLight];
                if(_directionalLight.mIsEnabled) _resultPhong += Phong(_directionalLight, o_normale, _albedoColor);
        }
        
        vec3 _result = _ambient + _resultPhong;
        FragColor = vec4(_result,1.0);
}