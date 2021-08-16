#pragma once
#include <iostream>
#include <map>
#include <string>

#include "../../glad/glad.h"
#include "../../lib/glfw-3.3.2.bin.WIN32/include/GLFW/glfw3.h"
#include "../../glm/glm.hpp"
#include "../../glm/gtc/matrix_transform.hpp"
#include "../../glm/gtc/type_ptr.hpp"
#include "../shader/Shader.h"

#include "../../lib/freetype/include/ft2build.h"
#include FT_FREETYPE_H

class TextGenerator {

public:

	void setup();
	void RenderText(Shader& shader, std::string text, float x, float y, float scale, glm::vec3 color);

private:

	/// Holds all state information relevant to a character as loaded using FreeType
	struct Character {
		unsigned int TextureID; // ID handle of the glyph texture
		glm::ivec2   Size;      // Size of glyph
		glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
		unsigned int Advance;   // Horizontal offset to advance to next glyph
	};

	unsigned int VAO, VBO;
	std::map<GLchar, Character> Characters;
};