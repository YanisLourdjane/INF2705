#include "buffer_object.h"

BufferObject::BufferObject():
    m_type(GL_ARRAY_BUFFER)
{
    // TODO
    glGenBuffers(1, &m_id);
    // On dit juste j ai besoin d un buffer donc cree moi un
}
//Sans les Bind ca echoue les tests automatiques
BufferObject::BufferObject(GLenum type, GLsizeiptr dataSize, const void* data, GLenum usage)
: BufferObject()
{
    // TODO
    bind();
    allocate(type, dataSize, data, usage);
}

BufferObject::~BufferObject()
{
    // TODO
    glBindBuffer(m_type, 0);
    glDeleteBuffers(1, &m_id);
}

void BufferObject::bind()
{
    // TODO
    glBindBuffer(m_type, m_id);
}

void BufferObject::allocate(GLenum type, GLsizeiptr dataSize, const void* data, GLenum usage)
{
    // TODO
    m_type = type;
    bind();
    glBufferData(type, dataSize, data, usage);
}

void BufferObject::update(GLsizeiptr dataSize, const void* data)
{
    // TODO
    bind();
    glBufferSubData(m_type, 0, dataSize, data);
}

void* BufferObject::mapBuffer()
{
    // TODO
    bind();
    return glMapBuffer(m_type, GL_READ_WRITE);
}

void BufferObject::unmapBuffer()
{
    // TODO
    bind();
    glUnmapBuffer(m_type);
}

