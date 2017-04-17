#version 330

layout (location = 0) in vec3 position;

out vec4 color;

uniform mat4 model;
uniform mat4 projection;

void main()
{
	vec4 worldPosition =  model * vec4(position, 1.0f);
	gl_Position = projection * worldPosition;
	color = vec4(clamp(position, 0.0, 1.0), 1.0);
}
