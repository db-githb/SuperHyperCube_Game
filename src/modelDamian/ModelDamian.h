#pragma once
#include "../modelBase/ModelBase.h"

class ModelDamian : public ModelBase {

public:
	ModelDamian(Shader &inShader);
	void initialize();
	void generateRandomModel();
	void allocateObjectData();
};