#version 330 core

struct Light
{
	vec3 position;
	vec3 color;
	float intensity;
	bool enabled;
};

uniform sampler2D mAlbedo;

#define NB_LIGHTS 16
uniform Light lights[NB_LIGHTS];

in vec2 o_uv;
in vec3 o_pos;

out vec4 FragColor;

void main()
{
    vec4 _texelAlbedo = texture(mAlbedo, o_uv);

    float illumination = 0;
    for(int i = 0; i < NB_LIGHTS; i++)
    {
    	if(lights[i].enabled)
    	{
    		float distance = length(o_pos-lights[i].position);
    		float value = lights[i].intensity * 1000;
    		value /= (distance*distance);
    		illumination += value;
    	}
    }

    FragColor = _texelAlbedo * illumination;
}