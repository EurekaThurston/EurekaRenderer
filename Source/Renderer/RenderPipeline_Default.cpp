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
    SetMeshRenderContext("Suzanne", GL_TRIANGLES, *GetShader("DefaultShader"), *GetCamera("MainCamera"));
    SetMeshRenderContext("Suzanne.001", GL_TRIANGLES, *GetShader("DefaultShader"), *GetCamera("MainCamera"));

    GetMesh("Suzanne")->SetScale(glm::vec3(0.01f));
    GetMesh("Suzanne.001")->SetScale(glm::vec3(0.01f));

    // Light
    CreateDirectionalLight("Sun", glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 1.0f), 0.5f);
    GetDirectionalLight("Sun")->SetShaderDirectionalLight(*GetShader("DefaultShader"));

    // Setup renderer context
    SetupRendererContext();
    EnableDepthTest(true);
}

void Renderer::Render()
{
    // Clear the screen
    Clear(0.0f, 0.0f, 0.0f, 1.0f);

    // Update renderer context
    UpdateRendererContext();

    // Update directional light
    GetDirectionalLight("Sun")->SetShaderDirectionalLight(*GetShader("DefaultShader"));

    // Camera receives input
    GetCamera("MainCamera")->UpdateInput();
    GetCamera("MainCamera")->UpdateMatrix(*GetShader("DefaultShader"));

    // Draw call
    DrawMeshes();

    // Swap the buffers
    glfwSwapBuffers(m_window->GetWindow());
}
