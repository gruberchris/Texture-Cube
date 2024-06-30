#version 330 core
in vec4 color;
in vec2 textureCoordinate;

out vec4 fragColor;

uniform sampler2D texture0;
uniform vec4 cubeColor;

void main()
{
    fragColor = texture(texture0, textureCoordinate) * mix(color, cubeColor, 0.5 * (1.0 + sin(gl_FragCoord.x * 0.1 + cubeColor.r)));
}