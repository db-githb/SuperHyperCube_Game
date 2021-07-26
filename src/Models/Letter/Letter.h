#pragma once
#include "../modelBase/ModelBase.h"
#include "../../Application/Transform.h"

#define WALL 1
#define BLUE 2
#define RED 3
#define NONE 0

#define sizeX 7
#define sizeY 9
#define sizeZ 1

class Letter : public ModelBase {

	

public:
	enum class ColorMode { col1, col2, col3, col4, col5 };
	glm::vec3 initialPosition = glm::vec3(0,0,0);
	ColorMode colorMode = ColorMode::col1;
	Transform transform;
	Letter();
	void Draw(Shader& shader);
	void GenerateLetter();
	void GenerateE();
	void GenerateL();
	void GenerateI();
	void GenerateJ();
	void GenerateA();

private:
	int letter[sizeX][sizeY];
};