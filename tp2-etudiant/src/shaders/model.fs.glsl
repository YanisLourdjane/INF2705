#version 330 core

uniform sampler2D myTexture;
in vec2 texturePos;
out vec4 outColor;

void main()
{
     vec4 color = texture( myTexture, texturePos );

    if (color.a < 0.3) {
        discard;
    }

    outColor = color;
}
