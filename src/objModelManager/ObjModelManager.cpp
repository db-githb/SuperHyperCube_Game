#include "ObjModelManager.h"

ObjModelManager::ObjModelManager() {
	objArr = new Model * [3]{ new Model("res/objects/tree7.obj"), new Model("res/objects/richierReduced.obj"), new Model("res/objects/leaf.obj") };

	fallingLeafPos = new glm::vec3 * [10]{
		new glm::vec3(-12.0f, 0.1, -4.0f),
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

	deltaTime = 0.0f;
	lastTime = 0.0f;


}

void ObjModelManager::renderObjModels(Shader& inShader) {
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(25.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(-16.0f, 0.0f, -10.0f));
	model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
	inShader.setMat4("model", model);
	objArr[0]->Draw(inShader);

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(6.0f, 0.0f, 2.0f));
	inShader.setMat4("model", model);
	objArr[1]->Draw(inShader);

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(-6.0f, 0.0f, 2.0f));
	model = glm::scale(model, glm::vec3(-1.0f, 1.0f, 1.0f));
	inShader.setMat4("model", model);
	objArr[1]->Draw(inShader);

	float currentTime = (float)glfwGetTime();
	deltaTime = currentTime - lastTime;
	lastTime = currentTime;

	fallValue -= deltaTime;
	prevSwingValueX = swingValueX;

	if (fallValue >= 0.11) {
		swingValueX = cos(glfwGetTime()) * 1.35;
	}
	else {
		swingValueX = prevSwingValueX;
		fallValue = 15.0f;
	}

	model = glm::mat4(1.0f);
	glm::vec3 transVec = glm::vec3(fallingLeafPos[0]->x + swingValueX, fallValue, fallingLeafPos[0]->z);
	model = glm::translate(model, transVec);
	inShader.setMat4("model", model);
	objArr[2]->Draw(inShader);
}