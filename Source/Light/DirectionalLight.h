#pragma once
#include <string>

#include "Light.h"

class DirectionalLight : public Light
{
public:
    DirectionalLight( glm::vec3 direction, glm::vec3 color, float intensity );

    glm::vec4 GetPosition() const override;
    void SetShaderDirectionalLight( Shader& shader ) const;

private:
    std::string m_name;
};
