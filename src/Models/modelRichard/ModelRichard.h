#pragma once
#include "../modelBase/ModelBase.h"

class ModelRichard : public ModelBase {

public:
	ModelRichard(Shader& inShader);
	void generateRandomModel();
	void generateOriginalObject();
	void allocateObjectData();


private:
	void resetModel();
};