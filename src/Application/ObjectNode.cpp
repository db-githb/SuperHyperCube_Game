#include "ObjectNode.h"

ObjectNode::ObjectNode()
{
	transform = Transform();
	parent = NULL;
	m_model = NULL;
}

ObjectNode::ObjectNode(ModelBase* model)
{
	parent = NULL;
	transform = Transform();
	m_model = model;
}

ObjectNode::~ObjectNode(void)
{
	for (unsigned int i = 0; i < children.size(); ++i)
	{
		delete children[i];
	}
}

void ObjectNode::AddChild(ObjectNode* objectNode)
{
	children.push_back(objectNode);
	objectNode->parent = this;
}

void ObjectNode::Draw(Shader &shader)
{
	if (m_model)
		m_model->Draw(shader);
	for (int i = 0; i < children.size(); i++)
		children[i]->Draw(shader);
}

void ObjectNode::Update(float ms)
{
	return;
}

void ObjectNode::SetModel(ModelBase* m)
{
	m_model = m;
	return;
}
