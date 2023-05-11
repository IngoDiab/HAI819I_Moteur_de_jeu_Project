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

struct DirectionalLight
{
    vec3 mLightColor;
    vec3 mLightDirection;
    bool mIsEnabled;
};
uniform DirectionalLight mDirectionalLights[NB_POINT_LIGHTS];

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

vec3 Phong(PointLight _pointLight, vec3 _normal, vec3 _albedoColor)
{
    vec3 _lightColor = _pointLight.mLightPower*_pointLight.mLightColor/(length(_pointLight.mLightPos - o_positionWorld)*length(_pointLight.mLightPos - o_positionWorld));

    vec3 _lightDirection = normalize(_pointLight.mLightPos - o_positionWorld);
    float _clampedDotDiffuse = max(dot(_lightDirection, _normal), 0.0);
    vec3 _diffuse = mDiffuse * _albedoColor * _clampedDotDiffuse * _lightColor;

    vec3 _viewDirection = normalize(cameraPosition-o_positionWorld);
    vec3 _reflectDirection = reflect(-_lightDirection,_normal);
    float _clampedDotSpecular = pow(max(dot(_viewDirection, _reflectDirection), 0.0), mShininess);
    vec3 _specular = mSpecular * _clampedDotSpecular *_lightColor;

    return _diffuse + _specular;
}

vec3 Phong(DirectionalLight _dirLight, vec3 _normal, vec3 _albedoColor)
{
    vec3 _lightDirection = normalize(-_dirLight.mLightDirection);
    float _clampedDotDiffuse = max(dot(_lightDirection, _normal), 0.0);
    vec3 _diffuse = mDiffuse * _albedoColor * _clampedDotDiffuse * _dirLight.mLightColor;

    vec3 _viewDirection = normalize(cameraPosition-o_positionWorld);
    vec3 _reflectDirection = reflect(normalize(_dirLight.mLightDirection),_normal);
    float _clampedDotSpecular = pow(max(dot(_viewDirection, _reflectDirection), 0.0), mShininess);
    vec3 _specular = mSpecular * _clampedDotSpecular *_dirLight.mLightColor;

    return _diffuse + _specular;
}


void main()
{
    vec3 _normal = normalize(o_normale);
//     if(mUseNormalMap){
//         vec3 texelNormalMap = texture(mNormalMap, o_uv).rgb*2.0-1.0;
//         _normal = normalize(o_TBN * texelNormalMap);
//     }
    vec3 _albedoColor = texture(mAlbedo, o_uv).rgb;
    vec3 _ambient = mAmbient * _albedoColor;

    int _nbLight = 0;
    vec3 _resultPhong = vec3(0,0,0);
    for(int _indexLight = 0; _indexLight<NB_POINT_LIGHTS; ++_indexLight)
    {
        PointLight _pointLight = mPointLights[_indexLight];
        if(_pointLight.mIsEnabled) _resultPhong += Phong(_pointLight, _normal, _albedoColor);

        DirectionalLight _directionalLight = mDirectionalLights[_indexLight];
        if(_directionalLight.mIsEnabled) _resultPhong += Phong(_directionalLight, _normal, _albedoColor);
    }
    
    vec3 _result = _ambient + _resultPhong;
    if(mEmissivness == 0) FragColor = vec4(_result,1.0);
    else FragColor = vec4(_albedoColor * mEmissivness,1.0);

    //UNLIT
    // FragColor = vec4(_albedoColor,1.0);
}