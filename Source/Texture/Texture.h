#pragma once
#include <string>
#include <memory>
#include "glad/glad.h"

class Texture
{
public:
    Texture( const std::string path );
    ~Texture();

    void Bind(GLuint slot = 0) const;
    void Unbind() const;

private:
    // GLuint m_textureID;
    std::unique_ptr<GLuint, void(*)(GLuint*)> m_textureID;
    std::string m_filePath;
    unsigned char* m_localBuffer;
    int m_width, m_height, m_BPP;   // BPP = Bytes Per Pixel
};
