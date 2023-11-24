#pragma once
#include "glad/glad.h"

class VBO
{
public:
    VBO(const GLfloat* data, GLsizeiptr size);
    ~VBO();

    void Bind() const;
    void Unbind() const;

private:
    GLuint m_VboID;
};
