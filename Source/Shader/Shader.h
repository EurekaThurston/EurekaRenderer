#pragma once
#include <string>
#include <unordered_map>
#include "../Texture/Texture.h"

struct ShaderProgramSources
{
    std::string VertexSource;
    std::string FragmentSource;
};

class Shader
{

public:
    Shader( const std::string& filepath );
    ~Shader();

    void Use() const;

    // Uniforms
    void SetFloat4( const std::string& name, float v0, float v1, float v2, float v3 );
    void SetSampler2D (const std::string& name, GLint textureSlot);

private:
    std::string m_FilePath;
    unsigned int m_ShaderID;
    std::unordered_map<std::string, int> m_UniformLocationCache;
    
    ShaderProgramSources ParseShader( const std::string& filepath );
    unsigned int CompileShader( unsigned int type, const std::string& source );
    unsigned int CreateShader( const std::string& vertexShader, const std::string& fragmentShader );
    int GetUniformLocation( const std::string& name );
};
