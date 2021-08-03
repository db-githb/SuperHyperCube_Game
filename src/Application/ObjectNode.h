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
	std::vector<ObjectNode*> children;
	

	const glm::vec3& GetPosition();
	const glm::vec3& GetRotation();
	const glm::vec3& GetScale();

	void SetPosition(glm::vec3 pos);
	void SetRotation(glm::vec3 rot);
	void SetScale(glm::vec3 scale);

	void AddPosition(glm::vec3 pos);
	void AddRotation(glm::vec3 rot);
	void AddScale(glm::vec3 scale);

protected:
	Transform transform;
	ObjectNode* parent;
	ModelBase* m_model;
	
	



};