#include <iostream>

#include "Renderer.h"

void Renderer::SetupContext()
{
    // Texture
    // AddTexture("Icon", "Resources/Textures/Icon.png");
    // AddTexture("Face", "Resources/Textures/Face.png");

    // Shader
    CreateShader("DefaultShader", "Source/Shader/Shaders/DefaultShader.glsl");
    GetShader("DefaultShader")->Use();
    // GetShader("DefaultShader")->SetSampler2D("Icon", 0);
    // GetShader("DefaultShader")->SetSampler2D("Face", 1);

    // Camera
    CreateCamera("MainCamera", m_window, glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f),
                 glm::vec3(0.0f, 1.0f, 0.0), 45.0f, 0.1f, 100.0f);

    // Model    
    ImportModel("Monkey", "Resources/Models/Monkey.fbx");
    CreateMeshFromModel(*GetModel("Monkey"));
    SetMeshRenderContext("Suzanne.001", GL_TRIANGLES, *GetShader("DefaultShader"), *GetCamera("MainCamera"));

    // Setup renderer context
    SetupRendererContext();
}

void Renderer::Render()
{
    // Clear the screen
    Clear();

    // Update renderer context
    UpdateRendererContext();

    // Camera receives input
    GetCamera("MainCamera")->UpdateInput();

    // Draw call
    DrawMeshes();

    // Swap the buffers
    glfwSwapBuffers(m_window->GetWindow());
}
