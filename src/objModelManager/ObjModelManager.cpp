#include "ObjModelManager.h"

ObjModelManager::ObjModelManager() {
	objArr = new Model * [4]{ new Model("res/objects/tree7.obj"), new Model("res/objects/richierReduced.obj"), new Model("res/objects/leaf.obj"),  new Model("res/objects/venus1.obj") };

	nrFallingLeaf = 10;

	fallingLeafPos = new glm::vec3 * [nrFallingLeaf]{
		new glm::vec3(-12.0f, 0.1f, -4.0f),
		new glm::vec3(-12.0f, 0.1f, -11.0f),
		new glm::vec3(-15.0f, 0.1f, 0.0f),
		new glm::vec3(-15.0f, 0.1f, -6.0f),
		new glm::vec3(-16.0f, 0.1f, 4.0f),
		new glm::vec3(-18.0f, 0.1f, -2.0f),
		new glm::vec3(-19.0f, 0.1f, 2.0f),
		new glm::vec3(-20.0f, 0.1f, 5.0f),
		new glm::vec3(-22.0f, 0.1f, -1.0f),
		new glm::vec3(-25.0f, 0.1f, 2.0f),
	};

	leafNumber = new int [nrFallingLeaf] {0, 9, 4, 1, 5, 9, 3, 8, 2, 6};
	indexToChooseWhichLeafIsFalling = 0;

	indexToChooseSecondLeaf = 9;
	secondLeafFallValue = secondLeafHeight;

	fallValue = firstLeafHeight;
	swingValueX = 0.0f;

	swingValueZ = 0.0f;
	prevSwingValueZ = 0.0f;
}

void ObjModelManager::renderObjModels(Shader& inShader, bool shadowMap) {

	// Tree Model
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(25.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(-16.0f, 0.0f, -10.0f));
	model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
	inShader.setMat4("model", model);
	objArr[0]->Draw(inShader);

	// Right Statue
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(6.0f, 0.0f, 2.0f));
	inShader.setMat4("model", model);
	objArr[1]->Draw(inShader);

	// Right Statue
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(-6.0f, 0.0f, 2.0f));
	model = glm::scale(model, glm::vec3(-1.0f, 1.0f, 1.0f));
	inShader.setMat4("model", model);
	objArr[1]->Draw(inShader);

	// Moon
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(6.5f, 21.5f, -6.0f));
	model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
	if (!shadowMap) {
		inShader.setMat4("model", model);
		inShader.setBool("moonAmbient", true);
		objArr[3]->Draw(inShader);
		inShader.setBool("moonAmbient", false);
	}


	// per-frame logic for falling leaves
	float currentTime = (float)glfwGetTime();
	deltaTime = currentTime - lastTime;
	lastTime = currentTime;

	fallValue -= deltaTime;

	int theActiveFallingLeaf = leafNumber[indexToChooseWhichLeafIsFalling];
	int theActiveLeaf2 = leafNumber[indexToChooseSecondLeaf];

	if (fallValue >= 0.11) {
		swingValueX = cos(glfwGetTime()) * 1.35;
	}
	else {
		fallingLeafPos[theActiveFallingLeaf]->x += swingValueX;
		fallValue = firstLeafHeight;
		indexToChooseWhichLeafIsFalling = indexToChooseWhichLeafIsFalling < (nrFallingLeaf-2) ? indexToChooseWhichLeafIsFalling+2 : 0;
	}

	// falling leaves
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(fallingLeafPos[theActiveFallingLeaf]->x + swingValueX, fallValue, fallingLeafPos[theActiveFallingLeaf]->z));
	inShader.setMat4("model", model);
	objArr[2]->Draw(inShader);

	// SECOND FALLING LEAF

	secondLeafFallValue -= deltaTime;

	if (secondLeafFallValue >= 0.11) {
		swingValueX = cos(glfwGetTime()) * 1.35;
	}
	else {
		fallingLeafPos[theActiveLeaf2]->x += swingValueX;
		secondLeafFallValue = secondLeafHeight;
		indexToChooseSecondLeaf = indexToChooseSecondLeaf < (nrFallingLeaf - 1) ? indexToChooseSecondLeaf + 2 : 1;
	}

	// falling leaves
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(fallingLeafPos[theActiveLeaf2]->x + swingValueX, secondLeafFallValue, fallingLeafPos[theActiveLeaf2]->z));
	inShader.setMat4("model", model);
	objArr[2]->Draw(inShader);

	// ground leaves
	for (int i = 0; i < nrFallingLeaf; i++) {

		model = glm::mat4(1.0f);
		if (i == theActiveFallingLeaf || i == theActiveLeaf2) {
			continue;
		}

		model = glm::translate(model, *fallingLeafPos[i]);
		inShader.setMat4("model", model);
		objArr[2]->Draw(inShader);
	}

}