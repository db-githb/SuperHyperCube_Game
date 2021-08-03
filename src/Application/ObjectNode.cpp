//#include "ObjectNode.h"
//
//ObjectNode::ObjectNode()
//{
//	transform = Transform();
//	parent = NULL;
//	m_model = NULL;
//}
//
//ObjectNode::ObjectNode(ModelBase* model)
//{
//	parent = NULL;
//	transform = Transform();
//	transform.SetPosition(glm::vec3(0,0.5f, -10.0f));
//	model->SetTransform(transform);
//	m_model = model;
//}
//
//ObjectNode::~ObjectNode(void)
//{
//	for (unsigned int i = 0; i < children.size(); ++i)
//	{
//		delete children[i];
//	}
//}
//
//void ObjectNode::AddChild(ObjectNode* objectNode)
//{
//	children.push_back(objectNode);
//	objectNode->parent = this;
//}
//
//void ObjectNode::Draw(Shader &shader)
//{
//	if (m_model)
//		m_model->Draw(shader);
//	for (int i = 0; i < children.size(); i++)
//		children[i]->Draw(shader);
//}    
//
//void ObjectNode::Update(float ms)
//{
//	return;
//}
//
//void ObjectNode::SetModel(ModelBase* m)
//{
//	m_model = m;
//	return;
//}
//
//void ObjectNode::SetPosition(glm::vec3 pos)
//{
//	transform.SetPosition(parent->transform.GetPosition() + pos);
//	for (ObjectNode* child : children)
//	{
//		child->SetPosition(pos);
//	}
//}
//
//void ObjectNode::SetRotation(glm::vec3 rot)
//{
//	transform.SetRotation(parent->transform.GetRotation() + rot);
//	for (ObjectNode* child : children)
//	{
//		child->SetRotation(rot);
//	}
//}
//
//void ObjectNode::SetScale(glm::vec3 sc)
//{
//	transform.SetScale(parent->transform.GetScale() + sc);
//	for (ObjectNode* child : children)
//	{
//		child->SetScale(sc);
//	}
//}
//
//void ObjectNode::AddPosition(glm::vec3 pos)
//{
//	transform.AddPosition(pos);
//	for (ObjectNode* child : children)
//	{
//		child->AddPosition(pos);
//	}
//}
//
//void ObjectNode::AddRotation(glm::vec3 rot)
//{
//	transform.AddRotation(rot);
//	for (ObjectNode* child : children)
//	{
//		child->AddRotation(rot);
//	}
//}
//
//void ObjectNode::AddScale(glm::vec3 sc)
//{
//	transform.AddScale(sc);
//	for (ObjectNode* child : children)
//	{
//		child->AddScale(sc);
//	}
//}
//
//
//const glm::vec3& ObjectNode::GetPosition()
//{
//	return transform.GetPosition();
//}
//
//const glm::vec3& ObjectNode::GetRotation()
//{
//	return transform.GetRotation();
//}
//
//const glm::vec3& ObjectNode::GetScale()
//{
//	return transform.GetScale();
//}