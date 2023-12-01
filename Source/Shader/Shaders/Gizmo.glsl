#include "Source/Shader/ShaderLibrary/Common.glsl"

// Shader Vertex
#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 3) in vec3 aColor;

out VertexOutput
{
    vec3 vertexColor;
} o;


void main()
{
    gl_Position = Matrix_P * Matrix_V * (vec4(aPos, 1.0));
    o.vertexColor = aColor;
}

// Shader Fragment
#version 460 core
out vec4 FragColor;

in VertexOutput
{
    vec3 vertexColor;
} i;

void main()
{

    FragColor = vec4(i.vertexColor, 1.0);
}

