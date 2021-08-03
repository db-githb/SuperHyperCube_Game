#include "Transform.h"

glm::vec3& Transform::GetPosition()
{
	return position;
}

glm::vec3& Transform::GetRotation()
{
	return rotation;
}

glm::vec3& Transform::GetScale()
{
	return scale;
}

void Transform::SetPosition(glm::vec3 pos)
{
	position = pos;
}

void Transform::SetRotation(glm::vec3 rot)
{
	rotation = rot;
}

void Transform::SetScale(glm::vec3 sc)
{
	scale = sc;
}

glm::mat4 Transform::GetModel() const
{
	glm::mat4 positionMatrix = glm::translate(position);

	glm::mat4 rotationXMatrix = glm::rotate(rotation.x, glm::vec3(1.0f, 0, 0));
	glm::mat4 rotationYMatrix = glm::rotate(rotation.y, glm::vec3(0, 1.0f, 0));
	glm::mat4 rotationZMatrix = glm::rotate(rotation.z, glm::vec3(0, 0, 1.0f));
	
	glm::mat4 scaleMatrix = glm::scale(scale);

	glm::mat4 rotationMatrix = rotationZMatrix * rotationYMatrix * rotationXMatrix;

	return positionMatrix * rotationMatrix * scaleMatrix;
}