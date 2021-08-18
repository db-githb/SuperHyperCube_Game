#pragma once
#include "../shader/Shader.h"
#include "../loadModel/loadModel.h"

class ObjModelManager {

public:
	ObjModelManager();
	void renderObjModels(Shader& inShader, bool shadowMap);

private:
	Model** objArr;
	glm::vec3** fallingLeafPos;
	glm::vec3** groundLeafPos;
	int* leafNumber;
	int nrFallingLeaf;
	int nrGroundLeaf;
	int indexToChooseWhichLeafIsFalling;

	float fallValue;
	float swingValueX;

	float swingValueZ;
	float prevSwingValueZ;

	float lastTime;
	float deltaTime;
};