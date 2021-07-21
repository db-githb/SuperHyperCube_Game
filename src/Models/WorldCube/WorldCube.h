#pragma once
#include "../modelBase/ModelBase.h"
#include "../../Application/Transform.h"

class WorldCube : public ModelBase
{


public:
	Transform transform;
	WorldCube();
	void Draw(Shader &shader);

private:
};

