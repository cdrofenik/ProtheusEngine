#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoordinate;

out vec4 color;
out vec2 texCoord;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

void main()
{
	vec4 worldPosition =  model * vec4(position, 1.0f);
	gl_Position = projection * view * worldPosition;
	color = vec4(clamp(position, 0.0, 1.0), 1.0);
	texCoord = texCoordinate;
}
