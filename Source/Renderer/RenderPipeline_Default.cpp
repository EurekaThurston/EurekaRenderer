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

    // Light
    CreateDirectionalLight(glm::vec3(1.0f, 1.0f, 1.0f),
                           glm::vec3(0.25f, 0.75f, 0.5f), 1.0f);
    SetDirectionalLightContext();

    // Setup renderer context
    SetupRendererContext();
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
    SetDirectionalLightContext();

    // Camera receives input
    GetCamera("MainCamera")->UpdateInput();

    // Draw call
    // Mesh objects
    DrawMeshes();

    // UI
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
