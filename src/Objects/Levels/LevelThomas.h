#pragma once

#include "../Level.h"

class LevelThomas : public Level {
public:
	LevelThomas(Shader& inShader);
	void generateObject() override;
};