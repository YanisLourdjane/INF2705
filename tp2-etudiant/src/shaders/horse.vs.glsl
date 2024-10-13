#version 330 core

uniform int index;
uniform mat4 MVP;
layout (location = 0) in vec3 inPos;
layout (location = 1) in vec2 inTexturePos;
out vec2 texturePos;

void main()
{
    float columns;
    fracCol = modf(index, &columns);

    float rows;
    fracRow = modf(index, rows);

    gl_Position = MVP * vec4(inPos, 1.0);
    texturePos = inTexturePos;
}