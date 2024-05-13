#version 430 core

layout (location = 0) out vec4 fragColor;

layout (location = 0) uniform sampler2D textureAtlas;

void main()
{
    fragColor = vec4(1.0);
}