uniform mat4 M;
uniform mat4 VP;

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


/* -------------------------------------------------------------------------- */
// Tranformations

vec4 TransformObjectToClip(vec4 v)
{
    return VP * M * v;
}