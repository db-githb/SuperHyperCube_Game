//Fragment Shader Code
#version 420

out vec4 FragColor;
uniform vec4 Color;

void main()
{	
	FragColor = vec4(Color);
};