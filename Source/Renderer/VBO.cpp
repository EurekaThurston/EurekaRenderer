#include "VBO.h"

VBO::VBO( const GLfloat* data, GLsizeiptr size )
{
    glGenBuffers(1, &m_VboID);
    Bind();
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VBO::~VBO()
{
    glDeleteBuffers(1, &m_VboID);
}

void VBO::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_VboID);
}

void VBO::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
