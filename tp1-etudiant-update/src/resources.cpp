#include "resources.h"

#include "utils.h"

#include "shader_object.h"

#include "vertices_data.h"

Resources::Resources()
: coloredTriangleBuffer(GL_ARRAY_BUFFER, sizeof(colorTriVertices), colorTriVertices, GL_STATIC_DRAW)
    , coloredSquareReduceBuffer(GL_ARRAY_BUFFER, sizeof(colorSquareVerticesReduced), colorSquareVerticesReduced, GL_STATIC_DRAW)
    , coloredSquareReduceIndicesBuffer(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes, GL_STATIC_DRAW)
{
    initShaderProgram(basic, "shaders/basic.vs.glsl", "shaders/basic.fs.glsl");
    initShaderProgram(color, "shaders/color.vs.glsl", "shaders/color.fs.glsl");
    initShaderProgram(transformColorAttrib, "shaders/transform.vs.glsl", "shaders/transform.fs.glsl");
    initShaderProgram(transformSolidColor, "shaders/transform.vs.glsl", "shaders/transform.fs.glsl");

    mvpLocationTransformColorAttrib = transformColorAttrib.getUniformLoc("MVP");
    // mvpLocationTransformSolidColor = transformSolidColor.getUniformLoc("MVP");
    // colorLocationTransformSolidColor = transformSolidColor.getUniformLoc("Color");
}

void Resources::initShaderProgram(ShaderProgram& program, const char* vertexSrcPath, const char* fragmentSrcPath)    
{
    // TODO
    //Pour les vertex:
    ShaderObject vertexShader(GL_VERTEX_SHADER, readFile(vertexSrcPath).c_str());
    program.attachShaderObject(vertexShader);

    //Pour les fragments:
    ShaderObject fragmentShader(GL_FRAGMENT_SHADER, readFile(fragmentSrcPath).c_str());
    program.attachShaderObject(fragmentShader);

    program.link();

    program.use();
}
