#include "ObjectNode.h"

ObjectNode::ObjectNode()
{
	transform = Transform();
	parent = NULL;
	m_model = NULL;
}

ObjectNode::ObjectNode(Model* model)
{
	parent = NULL;
	transform = Transform();
	model->SetTransform(&transform);
	transform.SetPosition(model->modelBasePosition);
	m_model = model;
	//m_model->SetGameObject(this);
}

// ObjectNode::~ObjectNode(void)
// {
// 	for (unsigned int i = 0; i < children.size(); ++i)
// 	{
// 		delete children[i];
// 	}
// }

void ObjectNode::AddChild(ObjectNode* objectNode)
{
	children.push_back(objectNode);
	objectNode->parent = this;
	if (objectNode->m_model)
		objectNode->m_model->parentTransform = &transform;
}

void ObjectNode::Draw(Shader& shader)
{
	if (m_model)
		m_model->draw(&shader);
	for (int i = 0; i < children.size(); i++)
		children[i]->Draw(shader);
}    

void ObjectNode::Update(float ms)
{ 
	// Update Children
	for(ObjectNode* child : children)
	{
		child->Update(ms);
	}
	return;
}

void ObjectNode::SetModel(Model* m)
{
	m_model = m;
	return;
}

void ObjectNode::SetPosition(glm::vec3 pos)
{
	glm::vec3 position = glm::vec3(0, 0, 0);

	if (parent != nullptr)
		position = parent->transform.GetRotation();

	transform.SetPosition(position + pos);
	
	for (ObjectNode* child : children)
	{
		child->SetPosition(pos + child->GetPosition());
	}
}

void ObjectNode::SetRotation(glm::vec3 rot)
{
	glm::vec3 rotation = glm::vec3(0, 0, 0);

	if (parent)
		rotation = parent->transform.GetRotation();
	
	transform.SetRotation(rotation + rot);
	
	for (ObjectNode* child : children)
	{
		child->SetRotation(rot);
	}
}

void ObjectNode::SetScale(glm::vec3 sc)
{
	transform.SetScale(parent->transform.GetScale() + sc);
	for (ObjectNode* child : children)
	{
		child->SetScale(sc);
	}
}

void ObjectNode::AddPosition(glm::vec3 pos)
{
	transform.AddPosition(pos);
	
}

void ObjectNode::AddRotation(glm::vec3 rot)
{
	transform.AddRotation(rot);
	
}

void ObjectNode::AddScale(glm::vec3 sc)
{
	transform.AddScale(sc);
}


const glm::vec3& ObjectNode::GetPosition()
{
	// glm::vec3 pos = transform.GetPosition();
	// std::cout << "\n position: x = " << pos.x << " y = " << pos.y << " z = " << pos.z << this;
	return transform.GetPosition();
}

const glm::vec3& ObjectNode::GetRotation()
{
	return transform.GetRotation();
}

const glm::vec3& ObjectNode::GetScale()
{
	return transform.GetScale();
}

Transform ObjectNode::getTransform()
{
	return transform;
}
