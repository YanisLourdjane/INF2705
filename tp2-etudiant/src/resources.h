#ifndef RESOURCES_H
#define RESOURCES_H

#include "shader_program.h"

#include "buffer_object.h"

class Resources
{
public:
    Resources();
    
    void initShaderProgram(ShaderProgram& program, const char* vertexSrcPath, const char* fragmentSrcPath);
    
    // Shaders    
    ShaderProgram model; 
    GLint mvpLocationModel;
    
    ShaderProgram horse;
    GLint mvpLocationHorse;
    GLint textureIndexLocationHorse;
};

#endif // RESOURCES_H
