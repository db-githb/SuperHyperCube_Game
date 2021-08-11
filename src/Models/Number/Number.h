#pragma once
#include "../modelBase/ModelBase.h"


#define COLUMNS 23
#define ROWS 7

class Number : public ModelBase {

	
public:
	Number(Shader& inShader);


	void generateOriginalObject();

	void draw(Shader* inShader) override;
private:
	int modelData[23][7];
	glm::mat4 positionMat;
	int sizeX, sizeY;
};