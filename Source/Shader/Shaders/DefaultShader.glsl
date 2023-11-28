#include "Source/Shader/ShaderLibrary/Common.glsl"

// Shader Vertex
#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;
layout (location = 3) in vec2 aTexCoord;

out vec2 uv;

void main()
{
    gl_Position = VP * vec4(aPos, 1.0);
    uv = aTexCoord;
    
}


// Shader Fragment
#version 460 core
out vec4 FragColor;

void main()
{
    FragColor = vec4(0.5, 0.5, 0.0, 1.0);
}
