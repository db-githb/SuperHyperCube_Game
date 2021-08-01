#pragma once
#include "../modelBase/ModelBase.h"

//#define ROWS 9
//#define COLUMNS 9
//#define PLANES 6
//
//#define NONE 6
//#define WALL 7
//
//#define GREEN 0
//#define BLUE 1
//#define	BROWN 2
//#define WHITE 3
//#define BLACK 4
//#define NUM_COLORS 5
//
//class ModelRichard : public ModelBase {
//
//public:
//	void initialize();
//	void draw(Camera inCam, glm::vec3* dirLight, glm::mat4 projection, glm::mat4 view, glm::mat4 model);
//	void generateRandomModel();
//	void generateOriginalObject();
//	void initializeColorPalette();
//
//private:
//	int modelData[ROWS][COLUMNS][PLANES];
//	void resetModel();
//	glm::vec3* colorPalette;
//};


class ModelRichard : public ModelBase {

public:
	ModelRichard(Shader& inShader);
	void generateRandomModel();
	void generateOriginalObject();
	void allocateObjectData();


private:
	void resetModel();
};