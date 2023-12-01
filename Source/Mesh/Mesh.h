#pragma once

#include <string>
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "../Camera/Camera.h"
#include "../Model/Model.h"
#include "../Misc/LifeSaving.h"

struct RenderContext
{
    GLenum mode;
    Shader* shader;
    Camera* camera;
    bool consoleLog = true;
};

class Mesh
{
public:
    Mesh( const std::string name, std::vector<VertexAttributes>& vertices, std::vector<GLuint>& indices );

    RenderContext m_renderContext;

    VAO m_vao;

    glm::vec3 GetPosition() const;
    void SetPosition( const glm::vec3& position );
    glm::vec3 GetRotation() const;
    void SetRotation( const glm::vec3& rotation );
    glm::vec3 GetScale() const;
    void SetScale( const glm::vec3& scale );
    glm::mat4 GetModelMatrix() const;
    void SetModelMatrix( const glm::mat4& modelMatrix );
    size_t GetVertexCount() const { return m_indices.size(); }

    void SetRenderContext( GLenum mode, Shader& shader, Camera& camera );
    void Draw();
    void DrawUI();

private:
    glm::vec3 m_position;
    glm::vec3 m_rotation;
    glm::vec3 m_scale;
    glm::mat4 m_modelMatrix;
    void UpdateModelMatrix();

    std::vector<VertexAttributes> m_vertices;
    std::vector<GLuint> m_indices;
};
