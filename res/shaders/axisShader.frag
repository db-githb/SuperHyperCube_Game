//Fragment Shader Code
#version 460 core

out vec4 FragColor;

uniform vec3 color;
uniform int xAxis;
uniform int yAxis;
uniform int zAxis;

void main()
{	
	if(xAxis == 1)
	{
		FragColor = vec4(color, 1.0f);
	}
	if(yAxis == 1)
	{
		FragColor = vec4(color, 1.0f);
	}
	if(zAxis == 1)
	{
		FragColor = vec4(color, 1.0f);
	}
};