#version 330 core

uniform sampler2D myTexture;
in vec2 texturePos;
out vec4 outColor;

void main()
{
    outColor = texture( myTexture, texturePos );
}
