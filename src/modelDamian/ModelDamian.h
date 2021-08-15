#pragma once
#include "../modelBase/ModelBase.h"

class ModelDamian : public ModelBase {

public:
	ModelDamian(Shader &inShader);
	void generateRandomModel();
	void allocateObjectData();
};