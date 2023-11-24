// Vertex Buffer Layout
#pragma once
#include <stdexcept>
#include <vector>
#include "glad/glad.h"


struct VertexBufferElement {
    unsigned int type;
    unsigned int count;
    unsigned char normalized;

    static unsigned int GetSizeOfType(unsigned int type) {
        switch (type) {
            case GL_FLOAT: return sizeof(GLfloat);
            case GL_UNSIGNED_INT: return sizeof(GLuint);
            case GL_UNSIGNED_BYTE: return sizeof(GLubyte);
        }
        return 0;
    }
};

class VertexBufferLayout
{
public:
    VertexBufferLayout() : m_stride(0) {}

    template <typename T>
    void Push( unsigned int count )
    {
        // static_assert(false);
        std::runtime_error(false);
    }

    template <>
    void Push<float>( unsigned int count )
    {
        m_elements.push_back({ GL_FLOAT, count, GL_FALSE });
        m_stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
    }

    template <>
    void Push<unsigned int>( unsigned int count )
    {
        m_elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
        m_stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
    }

    template <>
    void Push<unsigned char>( unsigned int count )
    {
        m_elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
        m_stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
    }


    inline const std::vector<VertexBufferElement>& GetElements() const { return m_elements; }
    inline GLuint GetStride() const { return m_stride; }

private:
    std::vector<VertexBufferElement> m_elements;
    GLuint m_stride;
};
