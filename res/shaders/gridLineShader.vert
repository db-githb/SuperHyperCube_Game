// Vertex Shader code
#version 420

layout (location = 0) in vec3 gridLinePos;
	
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
		gl_Position = projection * view * model * vec4(gridLinePos, 1.0);
};