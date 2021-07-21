#pragma once
#include <iostream>
#include <stdio.h>
#include <string.h>


#include "../../glad/glad.h"
#include "../../lib/glfw-3.3.2.bin.WIN32/include/GLFW/glfw3.h"
#include "../../glm/glm.hpp"
#include "../../glm/gtc/matrix_transform.hpp"
#include "../../glm/gtc/type_ptr.hpp"
#include "../Shader/Shader.h"
#include "../Camera/Camera.h"
#include "../Mesh/Mesh.h"
#include "../Application/Renderer.h"

class ObjectNode
{

public:
	ObjectNode(Mesh* m = NULL, glm::vec4 col = glm::vec4(1, 1, 1, 1));
	~ObjectNode(void);

	void AddChild(ObjectNode* objectNode);

	virtual void Update(float ms);
	virtual void Draw(const Renderer &renderer);

protected:
	ObjectNode* parent;
	Mesh* mesh;

	glm::mat4 worldTransform;
	glm::mat4 localTransform;
	glm::vec3 scale;
	glm::vec4 colour;

	std::vector<ObjectNode*> children;



};