#pragma once
#include "../unitCube/UnitCube.h"

class GridLines {
public:
	GridLines(Shader& gridLinesShader);
	void draw(glm::mat4 model, Shader &shadowMapShader);
	void pointLightProperties();

private:
	UnitCube unitCube;
	Shader gridLinesShader;
	unsigned int diffuseMap;
	//unsigned int specularMap;
};
