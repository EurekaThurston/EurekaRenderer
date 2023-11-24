#include "VBO.h"

VBO::VBO( const GLfloat* data, GLsizeiptr size )
{
    glGenBuffers(1, &m_vboID);
    Bind();
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VBO::~VBO()
{
    glDeleteBuffers(1, &m_vboID);
}

void VBO::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
}

void VBO::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::SetLayout( const VertexBufferLayout& layout )
{
    this->m_layout = layout;
}

void VBO::ActiveLayout() const
{
    Bind();
    const auto& elements = m_layout.GetElements();
    unsigned int offset = 0;
    for (unsigned int i = 0; i < elements.size(); i++) {
        const auto& element = elements[i];
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, element.count, element.type, 
                              element.normalized, m_layout.GetStride(), 
                              reinterpret_cast<const void*>(static_cast<uintptr_t>(offset)));
        offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
    }
}
