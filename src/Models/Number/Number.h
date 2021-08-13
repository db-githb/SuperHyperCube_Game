#pragma once
#include "../modelBase/Model.h"


#define COLUMNS 23
#define ROWS 7

class Number : public Model {

	
public:
	Number(Shader& inShader);


	void generateOriginalObject();

	void draw(Shader* inShader) override;
private:
	int cubePositions[23][7];
	glm::mat4 positionMat;
	int sizeX, sizeY;
};