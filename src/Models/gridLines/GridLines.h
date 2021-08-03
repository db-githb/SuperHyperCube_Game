#pragma once
#include "../../Mesh/unitCube/UnitCube.h"

class GridLines {
public:
	GridLines(Shader& inShader);
	void draw(glm::mat4 model, Shader &shadowMapShader);
	void pointLightProperties();
	void toggleTexture();

private:
	UnitCube unitCube;
	Shader gridLinesShader;
	unsigned int diffuseMap;
	bool textureOn;
	//unsigned int specularMap;
};
