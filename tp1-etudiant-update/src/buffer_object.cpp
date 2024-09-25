#include "buffer_object.h"

BufferObject::BufferObject() : m_type(GL_ARRAY_BUFFER)
{
    glGenBuffers(1, &m_id);
}

BufferObject::BufferObject(GLenum type, GLsizeiptr dataSize, const void *data, GLenum usage)
    : BufferObject()
{
    bind();
    allocate(type, dataSize, data, usage);
}

BufferObject::~BufferObject()
{
    glBindBuffer(m_type, 0);
    glDeleteBuffers(1, &m_id);
}

void BufferObject::bind()
{
    glBindBuffer(m_type, m_id);
}

void BufferObject::allocate(GLenum type, GLsizeiptr dataSize, const void *data, GLenum usage)
{
    m_type = type;
    bind();
    glBufferData(type, dataSize, data, usage);
}

void BufferObject::update(GLsizeiptr dataSize, const void *data)
{
    bind();
    glBufferSubData(m_type, 0, dataSize, data);
}

void *BufferObject::mapBuffer()
{
    bind();
    return glMapBuffer(m_type, GL_READ_WRITE);
}

void BufferObject::unmapBuffer()
{
    bind();
    glUnmapBuffer(m_type);
}
