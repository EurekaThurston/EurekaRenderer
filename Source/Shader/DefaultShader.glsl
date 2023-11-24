// Shader Vertex
#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec2 uv;

void main()
{
    gl_Position = vec4(aPos, 1.0);
    uv = aTexCoord;
    
}


// Shader Fragment
#version 460 core
out vec4 FragColor;

in vec2 uv;

uniform sampler2D TestTexture;

void main()
{
    FragColor = texture(TestTexture, uv);
}
