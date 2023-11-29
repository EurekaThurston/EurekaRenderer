#include "Renderer.h"

/* --------------------------------------------------------------- */
// Directional Light
DirectionalLight* Renderer::GetDirectionalLight( const std::string& lightName ) const
{
    return m_directionalLight;
}

void Renderer::CreateDirectionalLight( const std::string& lightName, glm::vec3 position, glm::vec3 color,
                                       float intensity )
{
    m_directionalLight = new DirectionalLight(position, color, intensity);
    DividingLine();
    std::cout << "Directional Light created: " << lightName << std::endl;
    DividingLine();
}
