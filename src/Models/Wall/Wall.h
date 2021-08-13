#pragma once
#include "../modelBase/ModelBase.h"
#include "../../Application/Transform.h"

#define WALL 1
#define BLUE 2
#define RED 3
#define NONE 0

#define sizeX 35
#define sizeY 9
#define sizeZ 1

class Wall : public ModelBase {


public:
	Transform transform;
	Wall();
	void Draw(Shader& shader);
	void generateWall();

private:
	int wall[sizeX][sizeY];
};