// The following uses code adapted from LearnOpenGL.com
// https://learnopengl.com/Model-Loading/Mesh

#pragma once

#ifndef MESH_H
#define MESH_H

#include "../../glad/glad.h"
#include "../../glm/glm.hpp"
#include "../../glm/gtc/matrix_transform.hpp"

#include "../shader/Shader.h"

#include <string>
#include <vector>
using namespace std;

struct Vertex {
	// position
	glm::vec3 Position;
	// normal
	glm::vec3 Normal;
	// texCoords
	glm::vec2 TexCoords;
	// tangent
	glm::vec3 Tangent;
	// bitangent
	glm::vec3 Bitangent;
};

struct Texture {
	unsigned int id;
	string type;
	string path;
};
#endif