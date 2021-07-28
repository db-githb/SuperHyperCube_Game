#pragma once
#include "../unitCube/UnitCube.h"
#include <stdlib.h>

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
#define NUM_COLORS 9

#define LIGHT_DIRECTION glm::vec3(-0.2f, -1.0f, -0.3f)
#define LIGHT_AMBIENT glm::vec3(0.05f, 0.05f, 0.05f)
#define LIGHT_DIFFUSE glm::vec3(0.4f, 0.4f, 0.4f)
#define LIGHT_SPECULAR glm::vec3(0.5f, 0.5f, 0.5f)

#define POINT_LIGHT_POSITION 0.0f, 30.0f, 0.0f

#define SCALE_UP 0
#define SCALE_DOWN 1

#define TRANS_RIGHT 0
#define TRANS_LEFT 1
#define TRANS_UP 2
#define TRANS_DOWN 3

#define ROTATE_RIGHT 0
#define ROTATE_LEFT 1

#define SCALE_MAX 2.0f
#define SCALE_MIN 0.1f

#define BOUND_X_MAX 10.0f
#define BOUND_X_MIN -10.0f
#define BOUND_Y_MIN 0.5f

class ModelBase {

public:

	struct Component {
		int*** modelData;
		
		Shader shader;

		unsigned int diffuseMap;
		unsigned int specularMap;
	};

	ModelBase();
	virtual void initialize();
	virtual void draw(Camera inCam, glm::mat4 projection, glm::mat4 view, glm::mat4 model);
	virtual void scale(int scaleDirection);
	virtual void translate(int translationDirection);
	virtual void rotate(int rotation);
	virtual void setRenderMode(int mode);
	virtual bool inBound(int direction);
	virtual void generateRandomModel();
	virtual void generateOriginalObject();
	virtual bool boundaryCollision();

	void shaderSetUp(Camera inCam, glm::mat4 projection, glm::mat4 view, Component component);

	static glm::vec3* colorPalette;
	static void setColorPalette();

protected:

	void allocateObjectData();
	void allocateWallData();
	void allocateShaderData();

	UnitCube unitCube;
	Component wall;
	Component object;

	glm::vec3 modelBasePosition;

	int rows;
	int columns;
	int planes;

	float scaleFactor;
	float xTranslation;
	float yTranslation;
	float zTranslation;

	int renderMode;

	/* orientation in radians */
	float orientation;

	void drawWall(glm::mat4 model);
	void drawObject(glm::mat4 model);
};