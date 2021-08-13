#pragma once
#include "../../modelBase/Model.h"


class ModelDamian : public Model {

public:
	ModelDamian(Shader &inShader);
	void initialize();
	void generateRandomModel();
	void allocateObjectData();
}; 
