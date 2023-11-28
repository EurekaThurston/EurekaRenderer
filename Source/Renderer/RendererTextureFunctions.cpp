#include "Renderer.h"

Texture* Renderer::GetTexture( const std::string& textureName )
{
    return m_textures[textureName];
}

void Renderer::ImportTexture( const std::string& textureName, const std::string& filePath )
{
    m_textures[textureName] = new Texture(filePath);
}
