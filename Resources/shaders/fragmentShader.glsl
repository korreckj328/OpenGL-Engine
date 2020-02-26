#version 330 core

// These need to match the names of the vertex shader outs exactly

in vec2 ourTextureCoordinates;

out vec4 color;

uniform sampler2D ourTexture1;

void main()
{
    color = texture(ourTexture1, ourTextureCoordinates);
}
