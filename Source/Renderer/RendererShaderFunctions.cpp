#include "Renderer.h"

/* --------------------------------------------------------------- */
// Shaders
Shader* Renderer::GetShader( const std::string& shaderName )
{
    return m_shaders[shaderName];
}

void Renderer::AddShader( const std::string& shaderName, const std::string& filePath )
{
    m_shaders[shaderName] = new Shader(filePath);
}