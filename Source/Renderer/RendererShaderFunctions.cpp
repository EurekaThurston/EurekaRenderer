#include "Renderer.h"

Shader* Renderer::GetShader( const std::string& shaderName )
{
    return m_shaders[shaderName];
}

void Renderer::CreateShader( const std::string& shaderName, const std::string& filePath )
{
    m_shaders[shaderName] = new Shader(filePath);
}

void Renderer::RecompileShader()
{
    if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_R) == GLFW_PRESS)
    {
        if (m_canRecompileShader)
        {
            for (auto& shader : m_shaders)
            {
                shader.second->RecompileShader();
                std::cout << "Recompiled shader: " << shader.first << std::endl;
            }
            m_canRecompileShader = false;
        }
    }
    if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_R) == GLFW_RELEASE)
    {
        m_canRecompileShader = true;
    }
}
