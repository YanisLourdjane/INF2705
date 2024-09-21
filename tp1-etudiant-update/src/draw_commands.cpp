#include "draw_commands.h"
#include <iostream>
using namespace std;


DrawArraysCommand::DrawArraysCommand(VertexArrayObject& vao, GLsizei count): m_vao(vao), m_count(count)
{
    // TODO: il fallait initialiser m_count et m_vao donc rien a ajouter
}

void DrawArraysCommand::draw()
{
    // TODO
    m_vao.bind();
    glDrawArrays(GL_TRIANGLES, 0, m_count);
}

void DrawArraysCommand::setCount(GLsizei count)
{
    // TODO
    m_count = count;
}

DrawElementsCommand::DrawElementsCommand(VertexArrayObject& vao, GLsizei count, GLenum type): m_vao(vao), m_count(count), m_type(type)
{
    // TODO: il fallait initialiser m_type et m_count et m_vao donc rien a ajouter
}

void DrawElementsCommand::draw()
{
    // TODO
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
    // TODO
    m_count = count;
}


