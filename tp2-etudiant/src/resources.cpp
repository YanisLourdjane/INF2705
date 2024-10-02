#include "resources.h"

#include "utils.h"

#include "shader_object.h"



Resources::Resources()
{
    // TODO - init des shaders
    initShaderProgram(model, "shaders/model.vs.glsl", "shaders/model.fs.glsl");
    initShaderProgram(horse, "shaders/horse.vs.glsl", "shaders/horse.fs.glsl");

    // location cube
    mvpLocationModel = model.getUniformLoc("MVP");
    // TODO: location caroussel (inclu couleur)
    mvpLocationHorse = horse.getUniformLoc("");
    textureIndexLocationHorse = horse.getUniformLoc("");

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