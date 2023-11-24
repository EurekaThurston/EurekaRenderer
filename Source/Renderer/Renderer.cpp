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
    for (auto& pair : m_textures)
    {
        delete pair.second;
    }
}

/* --------------------------------------------------------------- */
// Render Commands
void Renderer::Clear( GLfloat r, GLfloat g, GLfloat b, GLfloat a ) const
{
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
}


/* --------------------------------------------------------------- */
// Misc
void Renderer::GetMaxVertexAttributesSupported() const
{
    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
}
