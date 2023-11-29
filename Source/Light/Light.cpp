#include "Light.h"

#include "glm/vec4.hpp"

Light::Light()
{
}

Light::~Light()
{
}

glm::vec4 Light::GetPosition() const
{
    return { m_position, 1.0f };
}

glm::vec3 Light::GetColor() const
{
    return m_color;
}

float Light::GetIntensity() const
{
    return m_intensity;
}

void Light::SetPosition( glm::vec3 position )
{
    m_position = position;
}


void Light::SetColor( glm::vec3 color )
{
    m_color = color;
}

void Light::SetIntensity( float intensity )
{
    m_intensity = intensity;
}
