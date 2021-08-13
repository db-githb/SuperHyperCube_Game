#pragma once
#include "../Application/ObjectNode.h"

#define YAW_RIGHT 0
#define YAW_LEFT 1
#define PITCH_UP 2
#define PITCH_DOWN 3
#define ROLL_CLOCKWISE 4
#define ROLL_COUNTER_CLOCKWISE 5

#define sizeX 7
#define sizeY 9
#define sizeZ 7

#define WALL 1
#define BLUE 2
#define RED 3
#define NONE 0

class Level: public ObjectNode
{

	struct Data {
		int*** cubePositions;

		Shader shader;

		unsigned int diffuseMap;
		unsigned int specularMap;
	};
	
public:

	Level(Shader& inShader);
	Level(int*** objectPositions,int*** wallPositions);
	
	void Update(float ms) override;
	void RotateObject(int direction);
	bool ValidateOrientation();

	void generateObject();
	void generateWall();

	ObjectNode* wall;
	ObjectNode* object;

	
protected:

	glm::vec3 desiredRotation;
	
	
	int wallData[sizeX][sizeY][sizeZ];
	int objectData[sizeX][sizeY][sizeZ];
	
	
	
};
