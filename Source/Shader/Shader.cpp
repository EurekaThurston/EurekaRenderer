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
    // For debugging
    // std::cout << "Vertex Shader: " << source.VertexSource << std::endl;
    // std::cout << "Fragment Shader: " << source.FragmentSource << std::endl;
    *m_ShaderID = CreateShader(source.VertexSource, source.FragmentSource);
    m_FilePath = filepath;
}

Shader::~Shader()
{
    glDeleteProgram(*m_ShaderID);
}

ShaderProgramSources Shader::ParseShader( const std::string& filepath )
{
    // if file path points to a invalid file, return error shader
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
    bool versionTagPassed[2] = {false, false};  // Check if version tag is passed for include files so include files can be parsed correctly
    bool hasIncludeFile = false;
    std::string includeFilePath;

    while (getline(stream, line))
    {
        if (line.find("#include") != std::string::npos)
        {
            includeFilePath = ExtractIncludePath(line);
            hasIncludeFile = true;
        } 
        else if (line.find("// Shader") != std::string::npos)
        {
            if (line.find("Vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if (line.find("Fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else if (type != ShaderType::NONE)
        {
            if (!versionTagPassed[(int)type] && line.find("#version") != std::string::npos)
            {
                ss[(int)type] << line << "\n";
                if (hasIncludeFile)
                {
                    std::string includeContent = ReadIncludeFile(includeFilePath);
                    ss[(int)type] << includeContent << "\n";
                }
            } else
            {
                ss[(int)type] << line << "\n";
            }
        }
    }
    return { ss[0].str(), ss[1].str() };
}

std::string Shader::ReadIncludeFile( const std::string& filepath )
{
    std::ifstream stream(filepath);
    if (!stream) {
        std::cerr << "Failed to open include file: " << filepath << std::endl;
        return ""; // Return an empty string in case of failure
    }

    std::stringstream buffer;
    buffer << stream.rdbuf(); // Read the entire file into a string stream
    
    return buffer.str(); // Convert the string stream into a string and return it
}

std::string Shader::ExtractIncludePath( const std::string& line )
{
    std::string marker = "#include ";
    size_t startPos = line.find(marker);
    if (startPos != std::string::npos) {
        startPos += marker.length();
        // Expecting the path to be enclosed in quotes
        size_t firstQuotePos = line.find("\"", startPos);
        size_t lastQuotePos = line.find("\"", firstQuotePos + 1);
        if (firstQuotePos != std::string::npos && lastQuotePos != std::string::npos) {
            return line.substr(firstQuotePos + 1, lastQuotePos - firstQuotePos - 1);
        }
    }
    std::cerr << "Error: Incorrect format for '#include' in line: " << line << std::endl;
    return "";
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
        std::cout << "Fail to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" <<
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

void Shader::SetFloat4x4( const std::string& name, GLboolean transpose, const GLfloat* value )
{
    glUniformMatrix4fv(GetUniformLocation(name), 1, transpose, value);
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


