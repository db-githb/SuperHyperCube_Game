//Fragment Shader Code
#version 420

out vec4 FragColor;

uniform vec3 color;
uniform sampler2D image;
uniform bool textureOn;

in vec2 TexCoords;

void main()
{	
	if(textureOn){
		FragColor = texture(image, TexCoords);
	}
	else{
		FragColor = vec4(color, 1.0f);
	}
};