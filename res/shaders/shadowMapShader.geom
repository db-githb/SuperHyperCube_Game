/*
 * Geometry shader is from the learnOpenGL.com code repostitory on github: https://github.com/JoeyDeVries/LearnOpenGL
   License:
 * All code samples, unless explicitly stated otherwise, are licensed under the terms of the CC BY-NC 4.0 license as published by Creative Commons, either version 4 of the License, or (at your option) any later version.
 * Link to license:  https://github.com/JoeyDeVries/LearnOpenGL/blob/master/LICENSE.md
*/


// geometery shader
#version 420
layout (triangles) in;
layout (triangle_strip, max_vertices=18) out;

uniform mat4 shadowMatrices[6];

out vec4 FragPos; // FragPos from GS (output per emitvertex)

void main()
{
    for(int face = 0; face < 6; ++face)
    {
        gl_Layer = face; // built-in variable that specifies to which face we render.
        for(int i = 0; i < 3; ++i) // for each triangle's vertices
        {
            FragPos = gl_in[i].gl_Position;
            gl_Position = shadowMatrices[face] * FragPos;
            EmitVertex();
        }    
        EndPrimitive();
    }
} 