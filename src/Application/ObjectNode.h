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
#include "Transform.h"
#include "../Models/modelBase/ModelBase.h"

class ObjectNode
{

public:
	ObjectNode();
	~ObjectNode(void);
	ObjectNode(ModelBase* model);


	void SetModel(ModelBase* m);
	void AddChild(ObjectNode* objectNode);

	virtual void Update(float ms);
	virtual void Draw(Shader &shader);


protected:
	ObjectNode* parent;
	ModelBase* m_model;
	Transform transform;
	std::vector<ObjectNode*> children;



};