#include "VAO.h"

VAO::VAO()
{
    glGenVertexArrays(1, &m_VaoID);
    Bind();
}

VAO::~VAO()
{
    glDeleteVertexArrays(1, &m_VaoID);
}

void VAO::Bind() const
{
    glBindVertexArray(m_VaoID);
}

void VAO::Unbind() const
{
    glBindVertexArray(0);
}
