#version 330 core

uniform int index;  // Texture index in the grid
uniform mat4 MVP;

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec2 inTexturePos;
out vec2 texturePos;

void main()
{
    int numColumns = 2;
    int numRows = 3;

    // Compute column and row based on the index
    float colf, rowf, col, row;
    colf = index/float(numRows);
    rowf = index/float(numColumns);

    modf(colf, col);
    modf(rowf, row);

    // Calculate the size of each texture in the grid
    float colSize = 1.0 / float(numColumns);
    float rowSize = 1.0 / float(numRows);






    // Compute the texture offset based on column and row
    vec2 gridOffset = vec2(col * colSize, row * rowSize);

    // Scale the input texture coordinates to fit within one grid cell
    texturePos = inTexturePos * vec2(colSize, rowSize) + gridOffset;

    // Apply the MVP transformation to the vertex position
    gl_Position = MVP * vec4(inPos, 1.0);
}
