#version 330 core

uniform mat4 MVP;
uniform int index;
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 textureIn;
out vec2 texturePos;

void main()
{
    gl_Position = MVP * vec4(aPos, 1.0);

    ivec2 atlas = ivec2(2, 3);
    vec2 oneTexelSize = vec2(1.0 / float(atlas.x), 1.0 / float(atlas.y));  

    int row = index / atlas.x;
    int col = index % atlas.x;

    texturePos = textureIn * oneTexelSize + vec2(col, row) * oneTexelSize;
}
