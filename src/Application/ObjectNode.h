#pragma once

#include "../../glad/glad.h"
#include "../../lib/glfw-3.3.2.bin.WIN32/include/GLFW/glfw3.h"

#include "../../glm/glm.hpp"
#include "../../glm/gtc/matrix_transform.hpp"
#include "../../glm/gtc/type_ptr.hpp"
#include "../Shader/Shader.h"
#include "../Camera/Camera.h"


#include "Transform.h"
#include "Component.h"
#include "../Models/modelBase/Model.h"


class ObjectNode
{
public:

	Transform transform;
	ObjectNode* parent;
	Model* m_model;
	
	ObjectNode();
	ObjectNode(Model* model);

	void SetModel(Model* m);
	void AddChild(ObjectNode* objectNode);

	
	std::vector<ObjectNode*> children;
	std::vector<Component*> components;

	virtual void Update(float ms);
	virtual void Draw(Shader& shader);

	void SetPosition(glm::vec3 pos);
	void SetRotation(glm::vec3 rot);
	void SetScale(glm::vec3 scale);

	void AddPosition(glm::vec3 pos);
	void AddRotation(glm::vec3 rot);
	void AddScale(glm::vec3 scale);


	// TODO: Fix rotations such that they occur in world space instead of local space
	virtual void AddRotation90(glm::vec3 axis);
	
	const glm::vec3& GetPosition();
	const glm::vec3& GetRotation();
	const glm::vec3& GetScale();


	Transform getTransform();

private:
	int rotationXcount = 0;
	int rotationYcount = 0;
	int rotationZcount = 0;
	float rotations[4] = { 0.0f,90.0f,180.0f,270.0f};

};
