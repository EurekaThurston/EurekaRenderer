#pragma once

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>
#include<MathAdditional.h>

#include "../Shader/Shader.h"
#include "../Window/Window.h"
#include "../Renderer/RendererContext.h"


class Camera
{
public:
    // Camera constructor to set up initial values
    Camera(const std::string name , Window* window, glm::vec3 position, glm:: vec3 orientation, glm::vec3 up, float FOVdeg, float nearPlane, float farPlane);

    std::string m_name;
    Window* m_window;
    GLuint m_width;
    GLuint m_height;
    
    // Main CameraProperties
    glm::vec3 m_position;
    glm::vec3 m_orientation;
    glm::vec3 m_up;
    float m_fov;
    float m_nearPlane;
    float m_farPlane;
    
    // Movement
    float m_moveSpeed = 0.05f;
    // Rotation
    float m_sensitivity = 350.0f;

    // Camera lag
    glm::vec3 m_targetPosition;
    glm::vec3 m_targetOrientation;
    float m_positionLagFactor = 0.1f;
    float m_orientationLagFactor = 0.2f;

    // Prevents the camera from jumping around when first clicking left click
    bool m_firstClick = true;

    std::string GetName() {return m_name;}

    // Updates and exports the camera matrix to the Vertex Shader
    void UpdateMatrix(Shader& shader, const char* uniform);
    // Handles camera inputs
    void UpdateInput();
    void Movement();
    void Rotation();
    
};