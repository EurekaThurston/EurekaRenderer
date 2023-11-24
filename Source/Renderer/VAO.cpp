#include "VAO.h"

VAO::VAO()
{
    glGenVertexArrays(1, &m_vaoID);
    Bind();
}

VAO::~VAO()
{
    glDeleteVertexArrays(1, &m_vaoID);
}

void VAO::Bind() const
{
    glBindVertexArray(m_vaoID);
}

void VAO::Unbind() const
{
    glBindVertexArray(0);
}
