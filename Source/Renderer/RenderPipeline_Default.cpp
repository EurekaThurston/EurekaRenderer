#include <iostream>

#include "Renderer.h"

void Renderer::SetupContext()
{
    /* -------------------------------------------------------------------------- */
    // Import external assets
    // Texture
    // ImportTexture("Icon", "Resources/Textures/Icon.png");
    // ImportTexture("Face", "Resources/Textures/Face.png");

    // Model    
    ImportModel("Monkey", "Resources/Models/Monkey.fbx");
    ImportModel("Gizmo", "Resources/Models/Gizmo.fbx");
    /* -------------------------------------------------------------------------- */

    // Shader
    CreateShader("DefaultShader", "Source/Shader/Shaders/DefaultShader.glsl");
    CreateShader("GizmoShader", "Source/Shader/Shaders/Gizmo.glsl");

    // Camera
    CreateCamera("MainCamera", m_window, glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f),
                 glm::vec3(0.0f, 1.0f, 0.0), 45.0f, 0.1f, 100.0f);

    // Mesh objects
    CreateMeshFromModel(*GetModel("Monkey"), MeshTag::Object);
    SetMeshRenderContext("Suzanne", GL_TRIANGLES, *GetShader("DefaultShader"), *GetCamera("MainCamera"));

    // UI
    CreateMeshFromModel(*GetModel("Gizmo"), MeshTag::UI);
    SetUIRenderContext("Gizmo", GL_TRIANGLES, *GetShader("GizmoShader"), *GetCamera("MainCamera"));
    // GetUI("Gizmo")->SetPosition(glm::vec3(
    //     1.0f / static_cast<float>(m_window->GetWindowWidth()) * 100.0f * m_window->GetWindowAspectRatio(),
    //     1.0f / static_cast<float>(m_window->GetWindowHeight()) * 100.0f,
    //     -1.0f));
    GetUI("Gizmo")->SetPosition(glm::vec3(0.0f, 0.0f, -1.0f));

    // Light
    CreateDirectionalLight("Sun", glm::vec3(1.0f, 1.0f, 1.0f),
                           glm::vec3(1.0f, 1.0f, 1.0f), 1.0f);
    GetDirectionalLight("Sun")->SetShaderDirectionalLight(*GetShader("DefaultShader"));

    // Setup renderer context
    SetupRendererContext();
    EnableDepthTest(true);
}

void Renderer::Render()
{
    if (m_enterRenderLoop)
    {
        DividingStar();
        std::cout << "Render Loop: " << std::endl;
    }

    RecompileShader();

    // Clear the screen
    Clear(0.0f, 0.0f, 0.0f, 1.0f);

    // Update renderer context
    UpdateRendererContext();

    // Update directional light
    GetDirectionalLight("Sun")->SetShaderDirectionalLight(*GetShader("DefaultShader"));

    // Camera receives input
    GetCamera("MainCamera")->UpdateInput();

    // Draw call
    // Mesh objects
    EnableDepthTest(true);
    DrawMeshes();

    // UI
    // EnableDepthTest(false);
    DrawUIs();

    // Swap the buffers
    glfwSwapBuffers(m_window->GetWindow());

    if (m_enterRenderLoop)
    {
        std::cout << "End of Render Loop" << std::endl;
        DividingStar();
        m_enterRenderLoop = false;
    }
}
