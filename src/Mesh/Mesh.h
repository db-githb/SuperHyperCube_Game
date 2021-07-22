#pragma once
// The following uses code adapted from LearnOpenGL.com
// https://learnopengl.com/Model-Loading/Mesh

#include "../shader/Shader.h"

class Mesh {

public:
	void Draw(Shader &shader);
	virtual void setupMesh();
private:
	
};