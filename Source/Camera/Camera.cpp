#include"Camera.h"
#include <iostream>


Camera::Camera(const std::string name, Window* window, glm::vec3 position, glm:: vec3 orientation, glm::vec3 up, float FOVdeg, float nearPlane, float farPlane)
{
	m_name = name;
	m_window = window;
	m_width = window->GetWindowWidth();
	m_height = window->GetWindowWidth();
	m_position = position;
	m_targetPosition = position;
	m_orientation = orientation;
	m_targetOrientation = orientation;
	m_up = up;
	m_fov = FOVdeg;
	m_nearPlane = nearPlane;
	m_farPlane = farPlane;
	
}

void Camera::UpdateMatrix(Shader& shader, const char* uniform)
{
	// Makes camera look in the right direction from the right position
	glm::mat4 view = glm::lookAt(m_position, m_position + m_orientation, m_up);
	// Adds perspective to the scene
 	glm::mat4 projection = glm::perspective(glm::radians(m_fov), static_cast<float>(m_width) / static_cast<float>(m_height), m_nearPlane, m_farPlane);

	// Exports the camera matrix to the Vertex Shader
	shader.SetFloat4x4(uniform, GL_FALSE, glm::value_ptr(projection * view));
}

void Camera::UpdateInput()
{
	Movement();
	Rotation();
}

void Camera::Movement()
{
	glm::vec3 moveDir = glm::vec3(0.0f);
	GLFWwindow* window = m_window->GetWindow();
	
	// Handles key inputs
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		m_targetPosition += m_moveSpeed * m_orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		m_targetPosition -= m_moveSpeed * m_orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		m_targetPosition -= m_moveSpeed * glm::normalize(glm::cross(m_orientation, m_up));
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		m_targetPosition += m_moveSpeed * glm::normalize(glm::cross(m_orientation, m_up));
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		m_targetPosition += m_moveSpeed * m_up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
		m_targetPosition -= m_moveSpeed * m_up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		m_moveSpeed = 0.1f;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
	{
		m_moveSpeed = 0.05f;
	}
	// Interpolate the actual position towards the target position
	m_position = lerp(m_position, m_targetPosition, m_positionLagFactor);
}

void Camera::Rotation()
{
	GLFWwindow* window = m_window->GetWindow();

	// Handles mouse inputs
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{
		// Hides mouse cursor
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		// Prevents camera from jumping on the first click
		if (m_firstClick)
		{
			glfwSetCursorPos(window, static_cast<float>(m_width) / 2.0f, static_cast<float>(m_width) / 2.0f);
			m_firstClick = false;
		}

		// Stores the coordinates of the cursor
		double mouseX;
		double mouseY;
		// Fetches the coordinates of the cursor
		glfwGetCursorPos(window, &mouseX, &mouseY);

		// Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
		// and then "transforms" them into degrees 
		float rotX = m_sensitivity * (static_cast<float>(mouseY) - static_cast<float>(m_height) / 2.0f) / static_cast<float>(m_height);
		float rotY = m_sensitivity * (static_cast<float>(mouseX) - static_cast<float>(m_width) / 2.0f) / static_cast<float>(m_width);


		// Calculates upcoming vertical change in the Orientation
		glm::vec3 newOrientation = glm::rotate(m_orientation, glm::radians(-rotX), glm::normalize(glm::cross(m_orientation, m_up)));

		// Decides whether or not the next vertical Orientation is legal or not
		if (abs(glm::angle(newOrientation, m_up) - glm::radians(90.0f)) <= glm::radians(85.0f))
		{
			m_targetOrientation = newOrientation;
		}

		// Rotates the Orientation left and right
		m_targetOrientation = glm::rotate(m_targetOrientation, glm::radians(-rotY), m_up);
		// m_orientation = glm::rotate(m_orientation, glm::radians(-rotY), m_up);

		
		// Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
		glfwSetCursorPos(window, static_cast<float>(m_width)  / 2.0f, static_cast<float>(m_height) / 2.0f);
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		// Unhides cursor since camera is not looking around anymore
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		// Makes sure the next time the camera looks around it doesn't jump
		m_firstClick = true;
	}
	// Interpolate the actual orientation towards the target orientation
	m_orientation = slerp(m_orientation, m_targetOrientation, m_orientationLagFactor);
}