#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include "VBL.h"
#include "../Model/Model.h"

class VBO
{
public:
    VBO(std::vector<VertexAttributes>& vertices);
    ~VBO();

    void Bind() const;
    void Unbind() const;

    void SetLayout(const VertexBufferLayout& layout);
    void ActiveLayout() const;

private:
    GLuint m_vboID;
    VertexBufferLayout m_layout;
};
