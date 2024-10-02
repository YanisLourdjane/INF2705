#version 330 core

uniform vec2 texture;
in vec2 texturePos;

void main()
{
    outColor = vec4(color, 1.0);
}
