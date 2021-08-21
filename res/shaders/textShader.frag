//Fragment Shader Code
#version 420

in vec2 TexCoords;
out vec4 color;

/*
The fragment shader takes two uniforms: one is the mono-colored bitmap image of the glyph, and the other is a color uniform for adjusting the text's final color. 
We first sample the color value of the bitmap texture. Because the texture's data is stored in just its red component, we sample the r component of the texture as the sampled alpha value. 
By varying the output color's alpha value, the resulting pixel will be transparent for all the glyph's background colors and non-transparent for the actual character pixels. 
We also multiply the RGB colors by the textColor uniform to vary the text color.
*/
uniform sampler2D text;
uniform vec3 textColor;

void main()
{    
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);
    color = vec4(textColor, 1.0) * sampled;
}