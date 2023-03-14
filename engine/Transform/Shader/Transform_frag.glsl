#version 330 core

in vec3 o_position_model;

out vec4 FragColor;

void main(){
        const vec3 _centerColor = vec3(1,1,1);
        const vec3 _XColor = vec3(1,0,0);
        const vec3 _YColor = vec3(0,1,0);
        const vec3 _ZColor = vec3(0,0,1);

        if(o_position_model.x > 0.2) FragColor = vec4(_XColor,1);
        else if(o_position_model.y  > 0.2) FragColor = vec4(_YColor,1);
        else if(o_position_model.z  > 0.2) FragColor = vec4(_ZColor,1);
        else FragColor = vec4(_centerColor,1);
}