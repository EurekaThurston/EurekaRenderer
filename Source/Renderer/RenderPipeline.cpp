#include "Renderer.h"

void Renderer::SetupContext()
{
    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,  // top left 
        0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,   // top right
        0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f   // bottom right
    };
    GLuint indices[] = {
        // note that we start from 0!
        0, 2, 1, // first triangle
        0, 3, 2  // second triangle
    };

    // Context
    m_vao = new VAO();
    m_vbo = new VBO(vertices, sizeof(vertices));
    m_ebo = new EBO(indices, sizeof(indices));
    
    VertexBufferLayout layout;
    layout.Push<float>(3); // Position attribute
    layout.Push<float>(3); // Color attribute
    layout.Push<float>(2); // UV attribute
    m_vbo->SetLayout(layout);
    m_vbo->ActiveLayout();
    
    m_vao->Unbind();
    m_vbo->Unbind();
    m_ebo->Unbind();
    
    // Texture
    AddTexture("Icon", "Resources/Textures/Icon.png");
    AddTexture("Face", "Resources/Textures/Face.png");

    // Shader
    AddShader("DefaultShader", "Source/Shader/Shaders/DefaultShader.glsl");
    GetShader("DefaultShader")->Use();
    GetShader("DefaultShader")->SetSampler2D("Icon", 0);
    GetShader("DefaultShader")->SetSampler2D("Face", 1);
    
}

void Renderer::Render( GLFWwindow* window )
{
    // Clear the screen
    Clear();

    // Drawcalls
    m_vao->Bind();
    GetShader("DefaultShader")->Use();
    GetTexture("Icon")->Bind(0);
    GetTexture("Face")->Bind(1);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    m_vao->Unbind();

    // Swap the buffers
    glfwSwapBuffers(window);
}