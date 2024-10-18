#include "resources.h"

#include "utils.h"

#include "shader_object.h"



Resources::Resources()
{
    initShaderProgram(model, "shaders/model.vs.glsl", "shaders/model.fs.glsl");
    initShaderProgram(horse, "shaders/horse.vs.glsl", "shaders/model.fs.glsl");

    mvpLocationModel = model.getUniformLoc("MVP");
    
    mvpLocationHorse = horse.getUniformLoc("MVP");
    textureIndexLocationHorse = horse.getUniformLoc("index");
}

void Resources::initShaderProgram(ShaderProgram &program, const char *vertexSrcPath, const char *fragmentSrcPath)
{
    ShaderObject vertexShader(GL_VERTEX_SHADER, readFile(vertexSrcPath).c_str());
    program.attachShaderObject(vertexShader);

    ShaderObject fragmentShader(GL_FRAGMENT_SHADER, readFile(fragmentSrcPath).c_str());
    program.attachShaderObject(fragmentShader);

    program.link();
    program.use();
}