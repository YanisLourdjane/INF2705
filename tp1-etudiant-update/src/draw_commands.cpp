#include "draw_commands.h"
#include <iostream>
using namespace std;

DrawArraysCommand::DrawArraysCommand(VertexArrayObject &vao, GLsizei count) : m_vao(vao),
                                                                              m_count(count)
{
}

void DrawArraysCommand::draw()
{
    m_vao.bind();
    glDrawArrays(GL_TRIANGLES, 0, m_count);
}

void DrawArraysCommand::setCount(GLsizei count)
{
    m_count = count;
}

DrawElementsCommand::DrawElementsCommand(VertexArrayObject &vao, GLsizei count, GLenum type) : m_vao(vao),
                                                                                               m_count(count),
                                                                                               m_type(type)
{
}

void DrawElementsCommand::draw()
{
    m_vao.bind();
    glDrawElements(GL_TRIANGLES, m_count, m_type, 0);
    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        std::cout << "Draw command error: " << error << " at line " << __LINE__ << std::endl;
    }
}

void DrawElementsCommand::setCount(GLsizei count)
{
    m_count = count;
}
