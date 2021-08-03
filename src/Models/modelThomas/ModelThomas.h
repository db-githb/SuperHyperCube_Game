#pragma once
#include "../modelBase/ModelBase.h"

class ModelThomas : public ModelBase {

public:
	ModelThomas(Shader& inShader);
	void generateRandomModel();
	void generateOriginalObject();
	void allocateObjectData();


private:
	void resetModel();
};