#include "GridLines.h"

GridLines::GridLines(Shader &inShader) {
	unitCube = UnitCube();
	gridLinesShader =  Shader("res/shaders/baseShader.vert", "res/shaders/baseShader.frag");

	//diffuseMap = inShader.loadTexture("res/images/tile1.png");
	diffuseMap = inShader.loadTexture("res/images/tile3.png");
	//specularMap = inShader.loadTexture("res/images/brick_spec_map.png");

	textureOn = true;
}

// USE WITH TILE A

void GridLines::draw(glm::mat4 model, Shader &inShader) {
	
	inShader.use();
	
	inShader.setBool("textureOn", textureOn);
	inShader.setBool("borderOn", false);
	inShader.setFloat("specBias", 2.0);
	inShader.setVec3("colour", glm::vec3(0.8f, 0.0f, 0.8f));

	// with textureOn use 1 unit cube for better performance (no lag in movement) becuase when off 10 000 unit cubes are generated
	if (textureOn) {
		// bind texture maps
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseMap);

		model = glm::scale(model, glm::vec3(100.0, 0.01, 100.0));
		inShader.setMat4("model", model);

		glBindVertexArray(unitCube.getVAO());
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
	else {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindVertexArray(unitCube.getVAO());

		for (float x = -50.0; x < 51; x++) {
			for (float z = -50.0; z < 51; z++) {
				model = glm::mat4(1.0f);
				model = glm::translate(model, glm::vec3(x, 0.0f, z));
				model = glm::scale(model, glm::vec3(1.0, 0.01, 1.0));
				inShader.setMat4("model", model);
				
				glDrawArrays(GL_LINES, 0, 36);

			}
		}
	}

}

void GridLines::toggleTexture() {

	textureOn = !textureOn;
}