#pragma once
#include "glm/glm.hpp"
#include "../Shader/Shader.h"

class Light
{
public:
    Light();
    virtual ~Light();

    virtual glm::vec4 GetPosition() const;
    glm::vec3 GetColor() const;
    float GetIntensity() const;
    void SetPosition( glm::vec3 position );
    void SetColor( glm::vec3 color );
    void SetIntensity( float intensity );

protected:
    glm::vec3 m_position;
    glm::vec3 m_color;
    float m_intensity;
};
