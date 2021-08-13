#pragma once
#include "../../modelBase/Model.h"

class ModelRichard : public Model {

public:
	ModelRichard(Shader& inShader);
	void generateRandomModel();
	void generateOriginalObject();
	void allocateObjectData();


private:
	void resetModel();
};