#pragma once
#include "../Application/ObjectNode.h"

#define YAW_RIGHT 0
#define YAW_LEFT 1
#define PITCH_UP 2
#define PITCH_DOWN 3
#define ROLL_CLOCKWISE 4
#define ROLL_COUNTER_CLOCKWISE 5

#define sizeX 9
#define sizeY 9
#define sizeZ 7

#define NONE -2
#define WALL -1

#define GRAY 0
#define RED 1
#define BLUE 2
#define VIOLET 3
#define MINT 4
#define PINK 5
#define CYAN 6
#define YELLOW 7
#define ORANGE 8
#define BLACK 9
#define GREEN 10
#define BROWN 11
#define WHITE 12
#define NUM_COLORS 13


/// <summary>
/// Inherit from this class and override the generateObject() method to create your own level.
/// </summary>
class Level: public ObjectNode
{	
public:

	Level(Shader& inShader);
	
	void Update(float ms) override;
	bool validateOrientation();

	virtual void generateObject();
	void generateWall();
	void clearObjectModel();
	void clearWallModel();

	void resetLevel();
	void randomizeObjectOrientation();

	ObjectNode* wall;
	ObjectNode* object;

	
protected:
	
	int wallData[sizeX][sizeY][sizeZ];
	int objectData[sizeX][sizeY][sizeZ];
	
private:
	const glm::vec3 wallStartPosition = glm::vec3(0, 0, -10);
	const glm::vec3 objectStartPosition = glm::vec3(0, 0, 20);
	
};
