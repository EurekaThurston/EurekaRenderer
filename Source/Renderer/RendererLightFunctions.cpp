#include "Renderer.h"

/* --------------------------------------------------------------- */
// Directional Light
DirectionalLight* Renderer::GetDirectionalLight( const std::string& lightName ) const
{
    return m_directionalLight;
}

void Renderer::CreateDirectionalLight( glm::vec3 position, glm::vec3 color,
                                       float intensity )
{
    m_directionalLight = new DirectionalLight(position, color, intensity);
    DividingLine();
    std::cout << "Directional Light created " << std::endl;
    DividingLine();
}


void Renderer::SetDirectionalLightContext() const
{
    for (auto& shaderEntry : m_shaders)
    {
        Shader* shader = shaderEntry.second;
        if (shader)
        {
            shader->Use();
            m_directionalLight->SetShaderDirectionalLight(*shader);
        }
    }
}
