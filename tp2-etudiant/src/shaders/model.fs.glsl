#version 330 core

uniform sampler2D texture;
in vec2 texturePos;
out vec4 outColor;

void main()
{
    outColor = texture( texture, texturePos );
}
