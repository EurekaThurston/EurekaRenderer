#pragma once
#include "glad/glad.h"

class EBO
{
public:
    EBO(const GLuint* indices, GLsizeiptr size);
    ~EBO();

    void Bind() const;
    void Unbind() const;

private:
    GLuint m_EboID;
};
