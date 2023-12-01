/* -------------------------------------------------------------------------- */
// Structs
struct DirectionalLight
{
    vec3 Direction;
    vec4 Color;
    float Intensity;
};

struct Camera
{
    vec4 Position;
    vec4 Forward;
    float FrameSizeX;
    float FrameSizeY;
};


/* -------------------------------------------------------------------------- */
// Uniforms
uniform mat4 Matrix_M;
uniform mat4 Matrix_V;
uniform mat4 Matrix_P;
uniform Camera camera;
uniform DirectionalLight dirLight;

/* -------------------------------------------------------------------------- */
// Math funcionts

float lerp(float a, float b, float t)
{
    return a + t * (b - a);
}

vec2 lerp(vec2 a, vec2 b, float t)
{
    return a + t * (b - a);
}

vec3 lerp(vec3 a, vec3 b, float t)
{
    return a + t * (b - a);
}

vec4 lerp(vec4 a, vec4 b, float t)
{
    return a + t * (b - a);
}

float saturate(float x) {
    return clamp(x, 0.0, 1.0);
}

vec2 saturate(vec2 x) {
    return clamp(x, vec2(0.0), vec2(1.0));
}

vec3 saturate(vec3 x) {
    return clamp(x, vec3(0.0), vec3(1.0));
}

vec4 saturate(vec4 x) {
    return clamp(x, vec4(0.0), vec4(1.0));
}

/* -------------------------------------------------------------------------- */
// Tranformations

vec4 TransformObjectToClip(vec4 vertex)
{
    return Matrix_P * Matrix_V * Matrix_M * vertex;
}

vec4 TransformObjectToWorld(vec4 vertex)
{
    return Matrix_M * vertex;
}

vec4 TransformObjectToWorld(vec3 vertex)
{
    return Matrix_M * vec4(vertex, 1.0);
}

vec3 TransformObjectToWorldNormal(vec3 normal) {
    return (transpose(inverse(Matrix_M)) * vec4(normal, 0.0)).xyz;
}

/* -------------------------------------------------------------------------- */
// Light functions
vec3 DirectionalLightDirection()
{
    return normalize(dirLight.Direction);
}

/* -------------------------------------------------------------------------- */
// Camera functions
vec3 CameraDirection(vec3 vertex)
{
    return normalize(camera.Position.xyz - vertex);
}

vec3 CameraForward()
{
    return normalize(camera.Forward.xyz);
}