#include "ObjectNode.h"

ObjectNode::ObjectNode(Mesh* m, glm::vec4 col)
{
	mesh = m;
	colour = col;
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

void ObjectNode::Draw(const Renderer& renderer)
{
	/*if (mesh)
		mesh->Draw();*/
}

void ObjectNode::Update(float ms)
{

}