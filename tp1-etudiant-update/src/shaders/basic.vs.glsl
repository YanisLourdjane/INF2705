#version 330 core

// TODO
layout(location = 0) in vec3 inPos;

void main(){
    gl_Position = vec4(inPos, 1.0);
}