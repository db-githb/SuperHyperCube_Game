#pragma once
#include "../modelBase/ModelBase.h"

#define ROWS 9
#define COLUMNS 7
#define PLANES 5


#define WALL 0
#define BLUE 1
#define RED 2
#define NONE 3

class ModelThomas : public ModelBase {

public:
	void initialize();
	void draw(Camera inCam, glm::vec3* dirLight, glm::mat4 projection, glm::mat4 view, glm::mat4 model);

private:
	int modelData[ROWS][COLUMNS][PLANES];
};