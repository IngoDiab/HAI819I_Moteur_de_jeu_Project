#version 330 core

out vec4 FragColor;

void main()
{
    vec3 _debugColor = vec3(0.596f,0.984f,0.596f);
    FragColor = vec4(_debugColor,1);
}