#pragma once
#include "../modelBase/ModelBase.h"

class ModelThomas : public ModelBase {

public:
	void initialize();
	void generateRandomModel();
	void generateOriginalObject();
	void allocateObjectData();


private:
	void resetModel();
};