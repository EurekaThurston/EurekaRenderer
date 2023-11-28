#pragma once

#include <string>
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "../Camera/Camera.h"
#include "../Model/Model.h"

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
    std::string m_name;
    std::vector<VertexAttributes> m_vertices;
    std::vector<GLuint> m_indices;
    RenderContext m_renderContext;
    
    VAO m_vao;

    Mesh(const std::string name, std::vector<VertexAttributes>& vertices, std::vector<GLuint>& indices);
    std::string GetName() const { return m_name; }

    void SetRenderContext(GLenum mode, Shader& shader, Camera& camera);
    void Draw();
    
};
