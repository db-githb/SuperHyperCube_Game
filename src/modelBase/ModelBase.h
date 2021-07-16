#pragma once
#include "../unitCube/UnitCube.h"
#include <stdlib.h>

#define LIGHT_DIRECTION 0 
#define LIGHT_AMBIENT 1
#define LIGHT_DIFFUSE 2
#define LIGHT_SPECULAR 3

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
	ModelBase();
	virtual void initialize();
	virtual void draw(Camera inCam, glm::vec3* dirLight, glm::mat4 projection, glm::mat4 view, glm::mat4 model);
	virtual void scale(int scaleDirection);
	virtual void translate(int translationDirection);
	virtual void rotate(int rotation);
	virtual void setRenderMode(int mode);
	virtual bool inBound(int direction);
	virtual int* generateRandomModel(int rows, int columns, int planes);
	virtual void generateOriginalObject();

protected:
	UnitCube unitCube;
	Shader baseShader;
	glm::vec3 modelBasePosition;
	float scaleFactor;
	float xTranslation;
	float yTranslation;
	int renderMode;

	/* orientation in radians */
	float orientation;
};