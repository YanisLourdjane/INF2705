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
    ShaderProgram basic;
    ShaderProgram color;
    
    ShaderProgram transformColorAttrib; 
    GLint mvpLocationTransformColorAttrib;
    
    ShaderProgram transformSolidColor; 
    GLint mvpLocationTransformSolidColor;
    GLint colorLocationTransformSolidColor;
    
    // Buffer Objects    
    BufferObject coloredTriangleBuffer;
    
    BufferObject coloredSquareReduceBuffer;
    BufferObject coloredSquareReduceIndicesBuffer;
};

#endif // RESOURCES_H
