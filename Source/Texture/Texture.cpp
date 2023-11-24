#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#include <iostream>

Texture::Texture( const std::string path )
    : m_textureID(new GLuint(0), [](GLuint* ptr) {glDeleteTextures(1, ptr); delete ptr;}), m_filePath( path ), m_localBuffer( nullptr ), m_width( 0 ), m_height( 0 ), m_BPP( 0 )
{
    stbi_set_flip_vertically_on_load( 1 );
    m_localBuffer = stbi_load( path.c_str(), &m_width, &m_height, &m_BPP, 0 );

    if ( !m_localBuffer )
    {
        std::cout << "Failed to load texture: " << path << std::endl;
    }
    
    glGenTextures( 1, m_textureID.get() );
    glBindTexture( GL_TEXTURE_2D, *m_textureID );

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT );
    
    if ( m_localBuffer )
    {
        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_localBuffer );
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free( m_localBuffer );
    }
}

Texture::~Texture()
{
    glDeleteTextures(1, m_textureID.get());
}

void Texture::Bind( GLuint slot ) const
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, *m_textureID);
}

void Texture::Unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}
