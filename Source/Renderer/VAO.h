#pragma once
#include "glad/glad.h"

class VAO
{
public:
    VAO();
    ~VAO();

    void Bind() const;
    void Unbind() const;

private:
    GLuint m_VaoID;
};
