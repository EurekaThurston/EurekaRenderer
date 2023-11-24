#pragma once
#include "glad/glad.h"
#include "VBL.h"

class VBO
{
public:
    VBO(const GLfloat* data, GLsizeiptr size);
    ~VBO();

    void Bind() const;
    void Unbind() const;

    void SetLayout(const VertexBufferLayout& layout);
    void ActiveLayout() const;

private:
    GLuint m_vboID;
    VertexBufferLayout m_layout;
};
