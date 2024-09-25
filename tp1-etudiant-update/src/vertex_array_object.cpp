#include "vertex_array_object.h"

VertexArrayObject::VertexArrayObject()
{
    glGenVertexArrays(1, &m_id);
}

VertexArrayObject::~VertexArrayObject()
{
    unbind();
    glDeleteVertexArrays(1, &m_id);
}

void VertexArrayObject::bind()
{
    glBindVertexArray(m_id);
}

void VertexArrayObject::unbind()
{
    glBindVertexArray(0);
}

void VertexArrayObject::specifyAttribute(BufferObject &buffer, GLuint index, GLint size, GLsizei stride, GLsizeiptr offset)
{
    bind();
    buffer.bind();
    glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (void *)(offset * sizeof(GLfloat)));
    glEnableVertexAttribArray(index);
}
