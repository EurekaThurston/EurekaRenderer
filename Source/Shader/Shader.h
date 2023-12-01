#pragma once
#include <string>
#include <unordered_map>
#include <memory>
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
    unsigned int GetShaderID() const { return *m_shaderID; }
    std::string GetFilePath() const { return m_filePath; }
    unsigned int RecompileShader();

    // Uniforms
    void SetFloat( const std::string& name, float value );
    void SetFloat2( const std::string& name, float v0, float v1 );
    void SetFloat3( const std::string& name, float v0, float v1, float v2 );
    void SetFloat4( const std::string& name, float v0, float v1, float v2, float v3 );
    void SetFloat4x4( const std::string& name, GLboolean transpose, const GLfloat* value );
    void SetSampler2D( const std::string& name, GLint textureSlot );

private:
    std::string m_filePath;
    // unsigned int m_ShaderID;
    std::unique_ptr<GLuint, void(*)( GLuint* )> m_shaderID;
    std::unordered_map<std::string, int> m_uniformLocationCache;

    ShaderProgramSources ParseShader( const std::string& filepath );
    std::string ReadIncludeFile( const std::string& filepath );
    std::string ExtractIncludePath( const std::string& line );
    unsigned int CreateShader( const std::string& vertexShader, const std::string& fragmentShader );
    unsigned int CompileShader( unsigned int type, const std::string& source );
    unsigned int CompileErrorShader( unsigned int type );
    int GetUniformLocation( const std::string& name );

    // Error shader
    const char* m_errorVertexShaderSource = R"glsl(
    #version 460 core
    layout (location = 0) in vec3 aPos;
    void main() {
        gl_Position = vec4(aPos, 1.0);
    }
    )glsl";

    const char* m_errorFragmentShaderSource = R"glsl(
    #version 460 core
    out vec4 FragColor;
    void main() {
        FragColor = vec4(1.0f, 0.0f, 1.0f, 1.0f);
    }
    )glsl";
};
