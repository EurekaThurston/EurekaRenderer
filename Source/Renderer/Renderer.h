// Basic render pipeline for rendering a scene using forward rendering
#pragma once
#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "../Shader/Shader.h"
#include "../Texture/Texture.h"

class Renderer
{
public:
    Renderer();
    ~Renderer();
    
    // Renderer
    void SetupContext();
    void Render(GLFWwindow* window);

    // Shader
    Shader* GetShader(const std::string& shaderName);
    void AddShader(const std::string& shaderName, const std::string& filePath);

    // Texture
    Texture* GetTexture(const std::string& textureName);
    void AddTexture(const std::string& textureName, const std::string& filePath);
    
    // Misc
    void GetMaxVertexAttributesSupported() const;

private:
    // Renderer
    VAO* m_vao;
    VBO* m_vbo;
    EBO* m_ebo;

    // Shaders
    std::unordered_map<std::string, Shader*> m_shaders;

    // Textures
    std::unordered_map<std::string, Texture*> m_textures;

    // Render pipeline commands
    void Clear(GLfloat r = 0.5f, GLfloat g = 0.5f, GLfloat b = 0.5f, GLfloat a = 0.5f) const;
};
