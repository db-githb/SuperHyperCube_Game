// Vertex Shader code
#version 420

layout (location = 0) in vec3 linePos;
	
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
		gl_Position = projection * view * model * vec4(linePos, 1.0);
};