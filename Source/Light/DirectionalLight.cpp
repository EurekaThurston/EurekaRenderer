#include "DirectionalLight.h"
#include <iostream>

DirectionalLight::DirectionalLight( glm::vec3 direction, glm::vec3 color,
                                    float intensity )
{
    m_position  = direction;
    m_color     = color;
    m_intensity = intensity;
}

glm::vec4 DirectionalLight::GetPosition() const
{
    return { glm::normalize(m_position), 0.0f };
}

void DirectionalLight::SetShaderDirectionalLight( Shader& shader ) const
{
    shader.SetFloat3("dirLight.Direction", GetPosition().x, GetPosition().y, GetPosition().z);
    shader.SetFloat4("dirLight.Color", GetColor().x, GetColor().y, GetColor().z, 1.0f);
    shader.SetFloat("dirLight.Intensity", GetIntensity());
}
