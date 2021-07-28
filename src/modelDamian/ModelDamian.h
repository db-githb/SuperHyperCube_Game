#pragma once
#include "../modelBase/ModelBase.h"

class ModelDamian : public ModelBase {

public:
	void initialize();
	void generateRandomModel();
	void allocateObjectData();
	bool boundaryCollision();

private:
};