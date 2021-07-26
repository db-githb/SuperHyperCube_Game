#pragma once
#include "../modelBase/ModelBase.h"
#include "../../Application/Transform.h"

#define WALL 1
#define BLUE 2
#define RED 3
#define NONE 0

#define sizeX 7
#define sizeY 9
#define sizeZ 7

class ModelElijah : public ModelBase {


public:
	Transform transform;
	ModelElijah();
	void initialize();
	void draw(Camera inCam, glm::vec3* dirLight, glm::mat4 projection, glm::mat4 view, glm::mat4 model);
	void Draw(Shader& shader);
	void generateRandomModel();

	void generateOriginalObject();

private:
	int modelData[sizeX][sizeY][sizeZ];
};