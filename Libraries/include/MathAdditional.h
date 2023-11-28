#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

inline glm::vec3 lerp(const glm::vec3 a, const glm::vec3 b, float t)
{
    return a + t * (b - a);
}

inline glm::vec3 slerp(const glm::vec3& start, const glm::vec3& end, float t) {
    // Convert vectors to quaternions
    glm::quat startQuat = glm::quat(start);
    glm::quat endQuat = glm::quat(end);

    // Perform the spherical linear interpolation
    glm::quat slerpedQuat = glm::slerp(startQuat, endQuat, t);

    // Convert the quaternion back to a vector
    glm::vec3 result = glm::eulerAngles(slerpedQuat);

    return result;
}