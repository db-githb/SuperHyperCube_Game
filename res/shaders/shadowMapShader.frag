// fragment shader

/*
 * Fragment shader is from the learnOpenGL.com code repostitory on github: https://github.com/JoeyDeVries/LearnOpenGL
   License:
 * All code samples, unless explicitly stated otherwise, are licensed under the terms of the CC BY-NC 4.0 license as published by Creative Commons, either version 4 of the License, or (at your option) any later version.
 * Link to license:  https://github.com/JoeyDeVries/LearnOpenGL/blob/master/LICENSE.md
*/

#version 420

in vec4 FragPos;

uniform vec3 lightPos;
uniform float far_plane;

void main()
{
	float lightDistance = length(FragPos.xyz - lightPos);
	
	// map to [0;1] range by dividing by far_plane
	lightDistance = lightDistance/far_plane;

	// write this as modified depth
	gl_FragDepth = lightDistance;
}