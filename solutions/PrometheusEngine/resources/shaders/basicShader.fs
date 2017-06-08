#version 330

in vec4 color;
in vec2 texCoord;

out vec4 fragmentColor;

uniform sampler2D ourTexture;

void main()
{
    fragmentColor = texture(ourTexture, texCoord) * color;
}