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
    ImportModel("Monkey", "Resources/Models/TwoMonkeys.fbx");
    /* -------------------------------------------------------------------------- */

    // Shader
    CreateShader("DefaultShader", "Source/Shader/Shaders/DefaultShader.glsl");
    GetShader("DefaultShader")->Use();
    // GetShader("DefaultShader")->SetSampler2D("Icon", 0);
    // GetShader("DefaultShader")->SetSampler2D("Face", 1);

    // Camera
    CreateCamera("MainCamera", m_window, glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f),
                 glm::vec3(0.0f, 1.0f, 0.0), 45.0f, 0.1f, 100.0f);

    CreateMeshFromModel(*GetModel("Monkey"));
    SetMeshRenderContext("Suzanne.002", GL_LINES, *GetShader("DefaultShader"), *GetCamera("MainCamera"));
    SetMeshRenderContext("Suzanne.003", GL_LINES, *GetShader("DefaultShader"), *GetCamera("MainCamera"));

    GetMesh("Suzanne.002")->SetScale(glm::vec3(0.01f));
    GetMesh("Suzanne.003")->SetScale(glm::vec3(0.01f));


    // Setup renderer context
    SetupRendererContext();
}

void Renderer::Render()
{
    // Clear the screen
    Clear(0.0f, 0.0f, 0.0f, 1.0f);

    // Update renderer context
    UpdateRendererContext();

    // Camera receives input
    GetCamera("MainCamera")->UpdateInput();
    GetCamera("MainCamera")->UpdateMatrix(*GetShader("DefaultShader"), "VP");

    // Draw call
    DrawMeshes();

    // Swap the buffers
    glfwSwapBuffers(m_window->GetWindow());
}
