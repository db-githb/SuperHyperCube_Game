#pragma once
#include "../../Mesh/unitCube/UnitCube.h"
#include "../../Application/Component.h"

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

#define sizeX 9
#define sizeY 9
#define sizeZ 7


class Model : public Component{

public:

	struct Data {
		Shader shader;
		unsigned int diffuseMap;
		unsigned int specularMap;
	};

	Model(Shader &inShader);
	virtual ~Model();
	void Update(float ms);
	virtual void draw(Shader* inShader);

	virtual void setRenderMode(int mode);
	virtual void toggleTexture();
	virtual void toggleBorder();
	void resetObject();

	
	virtual void SetTransform(Transform* trans);

	static glm::vec3* colorPalette;
	static void setColorPalette();
	Transform* parentTransform;
	glm::vec3 modelBasePosition;
	int cubes[sizeX][sizeY][sizeZ];
	glm::vec3 cubePositions[sizeX][sizeY][sizeZ];
	Data data;

protected:

	void allocateModelData();

	Transform* transform;
	
	UnitCube unitCube;

	int renderMode;

	bool textureOn;
	bool borderOn;
	bool continuousOn;
	double continuousStartTime;

	void drawWall(Shader& inShader);
	void drawObject(Shader& inShader);
	void drawCube(Shader& inShader);
};
