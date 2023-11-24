#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <glad/glad.h>
#include "Shader.h"

Shader::Shader( const std::string& filepath )
    : m_ShaderID(new GLuint(0), [](GLuint* ptr) { glDeleteProgram(*ptr); delete ptr; })
{
    ShaderProgramSources source = ParseShader(filepath);
    *m_ShaderID = CreateShader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader()
{
    glDeleteProgram(*m_ShaderID);
}

ShaderProgramSources Shader::ParseShader( const std::string& filepath )
{
    std::ifstream stream(filepath);
    if (!stream) {
        std::cout << "Failed to open shader file: " + filepath << std::endl;
        return {m_errorVertexShaderSource, m_errorFragmentShaderSource};
    }

    enum class ShaderType
    {
        NONE     = -1,
        VERTEX   = 0,
        FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line))
    {
        if (line.find("// Shader") != std::string::npos)
        {
            if (line.find("Vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if (line.find("Fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else if (type != ShaderType::NONE)
        {
            ss[(int)type] << line << "\n";
        }
    }
    return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::CompileShader( unsigned int type, const std::string& source )
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "File to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" <<
            std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

unsigned int Shader::CompileErrorShader( unsigned type )
{
    unsigned int id = glCreateShader(type);
    const char* src = (type == GL_VERTEX_SHADER) ? m_errorVertexShaderSource : m_errorFragmentShaderSource;

    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    // Check for compilation errors
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cerr << "Error shader compilation failed: " << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

unsigned int Shader::CreateShader( const std::string& vertexShader, const std::string& fragmentShader )
{
    unsigned int program = glCreateProgram();
    unsigned int vs      = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs;
    if (vs == 0)
    {
        vs = CompileErrorShader(GL_VERTEX_SHADER);
        fs = CompileErrorShader(GL_FRAGMENT_SHADER);
    }
    else
    {
        fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
        if (fs == 0)
            fs = CompileErrorShader(GL_FRAGMENT_SHADER);
    }

    glAttachShader(program, vs);
    glAttachShader(program, fs);

    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

void Shader::Use() const
{
    glUseProgram(*m_ShaderID);
}

/* --------------------------------------------------------------- */
// Uniforms
void Shader::SetFloat4( const std::string& name, float v0, float v1, float v2, float v3 )
{
    glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

void Shader::SetSampler2D( const std::string& name, GLint textureSlot)
{
    glUniform1i(GetUniformLocation(name), textureSlot);
}

int Shader::GetUniformLocation( const std::string& name )
{
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        return m_UniformLocationCache[name];

    int location = glGetUniformLocation(*m_ShaderID, name.c_str());
    if (location == -1)
        std::cout << "Warning: uniform '" << name << "' doesn't exist" << std::endl;

    m_UniformLocationCache[name] = location;
    return location;
}


