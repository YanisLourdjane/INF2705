#include "vertex_array_object.h"

VertexArrayObject::VertexArrayObject()
{
    // TODO
    glGenVertexArrays(1, &m_id);
}

VertexArrayObject::~VertexArrayObject()
{
    // TODO
    unbind(); // CHANGES
    glDeleteVertexArrays(1, &m_id);
}

void VertexArrayObject::bind()
{
    // TODO
    glBindVertexArray(m_id);
}

void VertexArrayObject::unbind()
{
    // TODO
    glBindVertexArray(0);
}

void VertexArrayObject::specifyAttribute(BufferObject& buffer, GLuint index, GLint size, GLsizei stride, GLsizeiptr offset)
{
    // TODO
    bind();
    buffer.bind();
    glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride*sizeof(GLfloat), (void*)(offset*sizeof(GLfloat)));
    glEnableVertexAttribArray(index);
}
