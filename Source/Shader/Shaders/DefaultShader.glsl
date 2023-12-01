#include "Source/Shader/ShaderLibrary/Common.glsl"

// Shader Vertex
#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aColor;
layout (location = 4) in vec3 aTangent;

out VertexOutput
{
    vec3 posWS;
    vec3 nDirWS;
    vec2 uv;
} o;


void main()
{
    gl_Position = TransformObjectToClip(vec4(aPos, 1.0));
    o.posWS = TransformObjectToWorld(aPos).xyz;
    o.nDirWS = TransformObjectToWorldNormal(aNormal);
    o.uv = aTexCoord;

}


// Shader Fragment
#version 460 core
out vec4 FragColor;

in VertexOutput
{
    vec3 posWS;
    vec3 nDirWS;
    vec2 uv;
} i;

void main()
{
    vec3 nDirWS = normalize(i.nDirWS);
    vec3 lDirWS = DirectionalLightDirection();
    float NdotL = saturate(dot(nDirWS, lDirWS));
    NdotL = NdotL * 0.5 + 0.5;
    FragColor = NdotL * dirLight.Color * dirLight.Intensity;
}

