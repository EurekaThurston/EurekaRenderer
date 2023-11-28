#pragma once
#include <glad/glad.h>
#include <vector>

class EBO
{
public:
    EBO(std::vector<GLuint>& indices);
    ~EBO();

    void Bind() const;
    void Unbind() const;

private:
    GLuint m_eboID;
};
