#include "Renderer.h"

Shader* Renderer::GetShader( const std::string& shaderName )
{
    return m_shaders[shaderName];
}

void Renderer::CreateShader( const std::string& shaderName, const std::string& filePath )
{
    m_shaders[shaderName] = new Shader(filePath);
}
