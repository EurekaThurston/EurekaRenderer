#include "Renderer.h"

Camera* Renderer::GetCamera(const std::string& cameraName)
{
    return m_cameras[cameraName];
}
void Renderer::AddCamera(const std::string& cameraName, Window* window, glm::vec3 position, glm:: vec3 orientation, glm::vec3 up, float FOVdeg, float nearPlane, float farPlane)
{
    m_cameras[cameraName] = new Camera(cameraName, window, position, orientation, up, FOVdeg, nearPlane, farPlane);
}