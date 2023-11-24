#include <iostream>
#include "Renderer.h"

#include <stb/stb_image.h>

Renderer::Renderer()
{
    m_vao = nullptr;
    m_vbo = nullptr;
    m_ebo = nullptr;
}

Renderer::~Renderer()
{
    delete m_vao;
    delete m_vbo;
    delete m_ebo;
    for (auto& pair : m_shaders)
    {
        delete pair.second;
    }
}

/* --------------------------------------------------------------- */
// Renderer
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

    m_vao->Bind();
    m_vbo->Bind();
    m_ebo->Bind();

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // uv coordinate
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    m_vao->Unbind();


    // Texture
    AddTexture("Icon", "Resources/Textures/Icon.png");

    // Shader
    AddShader("DefaultShader", "Source/Shader/DefaultShader.glsl");
    GetShader("DefaultShader")->Use();
    GetShader("DefaultShader")->SetSampler2D("TestTexture", 0);
}

void Renderer::Render( GLFWwindow* window )
{
    // Clear the screen
    Clear();

    // Drawcalls
    m_vao->Bind();
    GetShader("DefaultShader")->Use();
    GetTexture("Icon")->Bind(0);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    m_vao->Unbind();

    // Swap the buffers
    glfwSwapBuffers(window);
}

/* --------------------------------------------------------------- */
// Render Commands
void Renderer::Clear( GLfloat r, GLfloat g, GLfloat b, GLfloat a ) const
{
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
}

/* --------------------------------------------------------------- */
// Shaders
Shader* Renderer::GetShader( const std::string& shaderName )
{
    return m_shaders[shaderName];
}

void Renderer::AddShader( const std::string& shaderName, const std::string& filePath )
{
    m_shaders[shaderName] = new Shader(filePath);
}

/* --------------------------------------------------------------- */
// Textures
Texture* Renderer::GetTexture( const std::string& textureName )
{
    return m_textures[textureName];
}

void Renderer::AddTexture( const std::string& textureName, const std::string& filePath )
{
    m_textures[textureName] = new Texture(filePath);
}

/* --------------------------------------------------------------- */
// Misc
void Renderer::GetMaxVertexAttributesSupported() const
{
    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
}
