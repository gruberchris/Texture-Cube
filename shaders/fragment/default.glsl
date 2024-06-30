#version 330 core
in vec4 color;
in vec2 textureCoordinate;

out vec4 fragColor;

uniform sampler2D texture0;

void main()
{
    fragColor = texture(texture0, textureCoordinate) * color;
}