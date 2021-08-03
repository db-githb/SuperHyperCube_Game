#pragma once
#include "../../Mesh/unitCube/UnitCube.h"
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
#define GREEN 10
#define BROWN 11
#define WHITE 12
#define NUM_COLORS 13

#define SCALE_UP 0
#define SCALE_DOWN 1

#define TRANS_RIGHT 0
#define TRANS_LEFT 1
#define TRANS_UP 2
#define TRANS_DOWN 3
#define TRANS_FORWARD 4
#define TRANS_BACKWARD 5

#define ROTATE_X_CLOCKWISE 0
#define ROTATE_X_COUNTER 1
#define ROTATE_Y_CLOCKWISE 2
#define ROTATE_Y_COUNTER 3
#define ROTATE_Z_CLOCKWISE 4
#define ROTATE_Z_COUNTER 5

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

	ModelBase(Shader &inShader);
	~ModelBase();
	virtual void draw(glm::mat4 model, Shader* inShader);
	virtual void scale(int scaleDirection);
	virtual void translate(int translationDirection);
	virtual void rotate(int rotation);
	virtual void setRenderMode(int mode);
	virtual void toggleTexture();
	virtual void toggleBorder();
	virtual void toggleContinuous();
	virtual void generateRandomModel();
	virtual void generateOriginalObject();
	virtual void resetObject();
	virtual void resetPOS();

	static glm::vec3* colorPalette;
	static void setColorPalette();

	glm::vec3 modelBasePosition;

protected:

	void allocateObjectData();
	void allocateWallData();

	UnitCube unitCube;
	Component wall;
	Component object;

	int rows;
	int columns;
	int planes;

	float scaleFactor;
	float xTranslation;
	float yTranslation;
	float zTranslation;

	int renderMode;

	bool textureOn;
	bool borderOn;
	bool continuousOn;
	double continuousStartTime;

	/* orientation in radians */
	float xRotation;
	float yRotation;
	float zRotation;

	void drawWall(glm::mat4 model);
	void drawObject(glm::mat4 model);
};