#pragma once
#include "../shader/Shader.h"
#include "../loadModel/loadModel.h"

class ObjModelManager {

public:
	ObjModelManager();
	void renderObjModels(Shader& inShader);

private:
	Model** objArr;
	glm::vec3** fallingLeafPos;
	glm::vec3** groundLeafPos;

	float fallValue = 15.0f;
	float swingValueX = 0.0f;
	float prevSwingValueX = 0.0f;

	float swingValueZ = 0.0f;
	float prevSwingValueZ = 0.0f;

	float lastTime;
	float deltaTime;
};