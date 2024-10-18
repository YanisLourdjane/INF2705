#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>

Texture2D::Texture2D(const char* path)
{
    int width, height, nChannels;
    stbi_set_flip_vertically_on_load(true);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    unsigned char* data = stbi_load(path, &width, &height, &nChannels, 0);
    if (data == NULL)
        std::cout << "Error loading texture \"" << path << "\": " << stbi_failure_reason() << std::endl;

    glGenTextures(1, &m_id);

    GLenum format = GL_RGB;
    if (nChannels == 1)
        format = GL_RED;
    else if (nChannels == 3)
        format = GL_RGB;
    else if (nChannels == 4)
        format = GL_RGBA;
    

    glBindTexture(GL_TEXTURE_2D, m_id);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);
}

Texture2D::~Texture2D()
{
    glDeleteTextures(1, &m_id);
}

void Texture2D::setFiltering(GLenum filteringMode)
{
    glBindTexture(GL_TEXTURE_2D, m_id);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filteringMode);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filteringMode );
}

void Texture2D::setWrap(GLenum wrapMode)
{
    glBindTexture(GL_TEXTURE_2D, m_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
}

void Texture2D::enableMipmap()
{
    glBindTexture(GL_TEXTURE_2D, m_id);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glGenerateMipmap( GL_TEXTURE_2D );
}

void Texture2D::use()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_id);
}

