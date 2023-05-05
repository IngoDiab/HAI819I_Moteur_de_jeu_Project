#version 330 core

in vec3 o_positionWorld;
in vec2 o_uv;
in vec3 o_normale;
in mat3 o_TBN;

out vec4 FragColor;

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

uniform vec3 mAmbient;
uniform vec3 mDiffuse;
uniform vec3 mSpecular;

//Implement
uniform bool mUseNormalMap;

uniform sampler2D mAlbedo;
uniform sampler2D mNormalMap;

uniform float mEmissivness;
uniform float mHeight;
uniform float mTiling;
uniform float mShininess;

vec3 Phong(PointLight _pointLight, vec3 _normal)
{
    vec3 _lightColor = 1000*_pointLight.mLightColor/(length(_pointLight.mLightPos - o_positionWorld)*length(_pointLight.mLightPos - o_positionWorld));

    vec3 _lightDirection = normalize(_pointLight.mLightPos - o_positionWorld);
    float _clampedDotDiffuse = max(dot(_lightDirection, _normal), 0.0);
    vec3 _diffuse = mDiffuse * _clampedDotDiffuse * _lightColor;

    vec3 _viewDirection = normalize(cameraPosition-o_positionWorld);
    vec3 _reflectDirection = reflect(-_lightDirection,_normal);
    float _clampedDotSpecular = pow(max(dot(_viewDirection, _reflectDirection), 0.0), mShininess);
    vec3 _specular = mSpecular * _clampedDotSpecular * _pointLight.mLightPower*_lightColor;

    return _diffuse;
}


void main()
{
    vec3 _normal = o_normale;
//     if(mUseNormalMap){
//         vec3 texelNormalMap = texture(mNormalMap, o_uv).rgb*2.0-1.0;
//         _normal = normalize(o_TBN * texelNormalMap);
//     }

    vec3 _resultPhong = vec3(0,0,0);
    for(int _indexPointLight = 0; _indexPointLight<NB_POINT_LIGHTS; ++_indexPointLight)
    {
        PointLight _pointLight = mPointLights[_indexPointLight];
        if(!_pointLight.mIsEnabled) continue;
        _resultPhong += Phong(_pointLight, _normal);
    }
    
    vec3 _result = mAmbient + _resultPhong;
    if(mEmissivness == 0) FragColor = vec4(texture(mAlbedo, o_uv).rgb * _result,1.0);
    else FragColor = vec4(texture(mAlbedo, o_uv).rgb * mEmissivness,1.0);
}