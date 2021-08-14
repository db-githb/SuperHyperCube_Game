#pragma once

#include "../Level.h"

class LevelDamian :
    public Level
{
public:
	LevelDamian(Shader& inShader);
	void generateObject() override;
};

