#pragma once
#include "../modelBase/ModelBase.h"


#define COLUMNS 9
#define ROWS 7
#define PLANES 7

class ModelElijah : public ModelBase {

	struct Transform
	{
		glm::vec3 position = glm::vec3(1.0f);
		glm::vec3 rotation = glm::vec3(1.0f);
		glm::vec3 scale	   = glm::vec3(1.0f);
		glm::mat4 matrix   = glm::mat4(1.0f);
	};

public:
	Transform transform;
	ModelElijah();
	void initialize();

	void generateRandomModel();

	void generateOriginalObject();

private:
	int modelData[9][7][7];
	glm::mat4 positionMat;
};