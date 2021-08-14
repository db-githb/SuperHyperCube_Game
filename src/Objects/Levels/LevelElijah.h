#pragma once

#include "../Level.h"

class LevelElijah :
    public Level
{
public:
	LevelElijah(Shader& inShader);
	void generateObject() override;
};

