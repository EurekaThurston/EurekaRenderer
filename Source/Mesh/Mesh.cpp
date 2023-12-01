#include "Mesh.h"

Mesh::Mesh( const std::string name, std::vector<VertexAttributes>& vertices, std::vector<GLuint>& indices )
{
    m_position = glm::vec3(0.0f);
    m_rotation = glm::vec3(0.0f);
    m_scale    = glm::vec3(1.0f);

    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix           = glm::translate(modelMatrix, m_position);
    modelMatrix           = glm::rotate(modelMatrix, glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    modelMatrix           = glm::rotate(modelMatrix, glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    modelMatrix           = glm::rotate(modelMatrix, glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    modelMatrix           = glm::scale(modelMatrix, m_scale);
    m_modelMatrix         = modelMatrix;

    m_renderContext.mode   = GL_TRIANGLES;
    m_renderContext.shader = nullptr;
    m_renderContext.camera = nullptr;

    m_vertices = vertices;
    m_indices  = indices;

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

glm::vec3 Mesh::GetPosition() const { return m_position; }
glm::vec3 Mesh::GetRotation() const { return m_rotation; }
glm::vec3 Mesh::GetScale() const { return m_scale; }
glm::mat4 Mesh::GetModelMatrix() const { return m_modelMatrix; }

void Mesh::SetPosition( const glm::vec3& position )
{
    m_position = position;
    UpdateModelMatrix();
}

void Mesh::SetRotation( const glm::vec3& rotation )
{
    m_rotation = rotation;
    UpdateModelMatrix();
}

void Mesh::SetScale( const glm::vec3& scale )
{
    m_scale = scale;
    UpdateModelMatrix();
}

void Mesh::UpdateModelMatrix()
{
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix           = glm::translate(modelMatrix, m_position);
    modelMatrix           = glm::rotate(modelMatrix, glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    modelMatrix           = glm::rotate(modelMatrix, glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    modelMatrix           = glm::rotate(modelMatrix, glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    modelMatrix           = glm::scale(modelMatrix, m_scale);
    m_modelMatrix         = modelMatrix;
}

void Mesh::SetModelMatrix( const glm::mat4& modelMatrix ) { m_modelMatrix = modelMatrix; }


void Mesh::SetRenderContext( GLenum mode, Shader& shader, Camera& camera )
{
    m_renderContext.mode   = mode;
    m_renderContext.shader = &shader;
    m_renderContext.camera = &camera;
}


void Mesh::Draw()
{
    m_renderContext.shader->Use();
    m_vao.Bind();
    m_renderContext.shader->SetFloat4x4("Matrix_M", false, glm::value_ptr(m_modelMatrix));
    m_renderContext.camera->UpdateMatrix(*m_renderContext.shader);
    glDrawElements(m_renderContext.mode, static_cast<GLsizei>(m_indices.size()), GL_UNSIGNED_INT, 0);
}

void Mesh::DrawUI()
{
    m_renderContext.shader->Use();
    m_vao.Bind();
    m_renderContext.shader->SetFloat4x4("Matrix_M", false, glm::value_ptr(m_modelMatrix));
    m_renderContext.camera->UpdateUIMatrix(*m_renderContext.shader);
    glDrawElements(m_renderContext.mode, static_cast<GLsizei>(m_indices.size()), GL_UNSIGNED_INT, 0);
}
