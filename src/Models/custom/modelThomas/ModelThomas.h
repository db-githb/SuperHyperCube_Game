#pragma once
#include "../../modelBase/Model.h"

class ModelThomas : public Model {

public:
	ModelThomas(Shader& inShader);
	void generateRandomModel();
	void generateOriginalObject();
	void allocateObjectData();


private:
	void resetModel();
};