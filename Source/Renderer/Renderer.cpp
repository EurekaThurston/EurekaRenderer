#include <iostream>
#include "Renderer.h"

Renderer::Renderer( Window* window )
{
    m_window    = window;
    m_DepthTest = true;
    // Setup context
    SetupContext();
}

Renderer::~Renderer()
{
    for (auto& pair : m_shaders)
    {
        delete pair.second;
    }
    for (auto& pair : m_textures)
    {
        delete pair.second;
    }
    for (auto& pair : m_cameras)
    {
        delete pair.second;
    }
    for (auto& pair : m_meshes)
    {
        delete pair.second;
    }
}

void Renderer::EnableDepthTest( bool enable ) const
{
    if (enable)
    {
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glfwWindowHint(GLFW_DEPTH_BITS, 24);
    }
    else
    {
        glDisable(GL_DEPTH_TEST);
    }
}

/* --------------------------------------------------------------- */
// Render Commands
void Renderer::Clear( GLfloat r, GLfloat g, GLfloat b, GLfloat a ) const
{
    glClearColor(r, g, b, a);
    if (m_DepthTest)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    else
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }
}

void Renderer::Draw( GLenum mode, GLsizei count, GLenum type, const GLvoid* indices ) const
{
    glDrawElements(mode, count, type, indices);
}

void Renderer::SetupRendererContext() const
{
    // For delta time
    RendererContext::GetInstance().lastFrameTime = glfwGetTime();
}


void Renderer::UpdateRendererContext() const
{
    // Upate delta time
    RendererContext::GetInstance().currentFrameTime = glfwGetTime();
    RendererContext::GetInstance().deltaTime = static_cast<float>(RendererContext::GetInstance().currentFrameTime -
        RendererContext::GetInstance().lastFrameTime);
    RendererContext::GetInstance().lastFrameTime = RendererContext::GetInstance().currentFrameTime;

    // Get frame rate
    RendererContext::GetInstance().fps = static_cast<unsigned int>(1.0f / RendererContext::GetInstance().deltaTime);
    std::cout << "FPS:" << RendererContext::GetInstance().fps << std::endl;
}


/* --------------------------------------------------------------- */
// Misc
void Renderer::GetMaxVertexAttributesSupported() const
{
    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
}
