#include "Mesh.h"

Mesh::Mesh(const std::string name, std::vector<VertexAttributes>& vertices, std::vector<GLuint>& indices)
{
    m_name = name;
    m_vertices = vertices;
    m_indices = indices;

    // Context
    m_vao.Bind();
    VBO m_vbo(vertices);
    EBO m_ebo(indices);
    
    VertexBufferLayout layout;
    layout.Push<float>(3); // Position
    layout.Push<float>(3); // Normal
    layout.Push<float>(2); // UV
    layout.Push<float>(4); // Vertex Color
    layout.Push<float>(4); // Tangent
    m_vbo.SetLayout(layout);
    m_vbo.ActiveLayout();
    
    m_vao.Unbind();
    m_vbo.Unbind();
    m_ebo.Unbind();
    
}

void Mesh::SetRenderContext( GLenum mode, Shader& shader, Camera& camera )
{
    m_renderContext.mode = mode;
    m_renderContext.shader = &shader;
    m_renderContext.camera = &camera;
}


void Mesh::Draw()
{
    m_renderContext.shader->Use();
    m_vao.Bind();
    m_renderContext.camera->UpdateMatrix(*m_renderContext.shader, "VP");
    glDrawElements(m_renderContext.mode,  static_cast<GLsizei>(m_indices.size()), GL_UNSIGNED_INT, 0);
}
