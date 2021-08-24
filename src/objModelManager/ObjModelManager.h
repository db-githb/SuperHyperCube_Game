#pragma once
#include "../shader/Shader.h"
#include "../loadModel/loadModel.h"

class ObjModelManager {

public:
	ObjModelManager();
	void renderObjModels(Shader& inShader, bool shadowMap);
	void turnPortalOn();
	void turnPortalOff();
private:
	Model** objArr;
	glm::vec3** fallingLeafPos;
	glm::vec3** groundLeafPos;

	float firstLeafHeight = 15.0f;
	float secondLeafHeight = 17.5;

	int* leafNumber;
	int nrFallingLeaf;
	int nrGroundLeaf;
	int indexToChooseWhichLeafIsFalling;

	int indexToChooseSecondLeaf;
	float secondLeafFallValue;

	float fallValue;
	float swingValueX;

	float swingValueZ;
	float prevSwingValueZ;

	float lastTime;
	float deltaTime;

	bool portalOn;
	float portalScale;
};