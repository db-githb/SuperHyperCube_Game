#pragma once
#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <../../glm/glm.hpp>
#include "../../glm/gtc/matrix_transform.hpp"
#include <../../glm/gtc/type_ptr.hpp>
#include <../../glm/gtx/transform.hpp>




class Transform
{
public:
	Transform(const glm::vec3& position = glm::vec3(), const glm::vec3& rotation = glm::vec3(), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f));
	const glm::vec3& GetPosition();
	const glm::vec3& GetRotation();
	const glm::vec3& GetScale();
	
	void SetPosition(glm::vec3 pos);
	void SetRotation(glm::vec3 rot);
	void SetScale(glm::vec3 scale);

	void AddPosition(glm::vec3 pos);
	void AddRotation(glm::vec3 rot);
	void AddScale(glm::vec3 scale);

	glm::mat4 GetModel() const;


protected:
private:
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;


};


#endif // TRANSFORM_H