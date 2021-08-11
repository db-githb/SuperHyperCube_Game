#include "GridLines.h"

GridLines::GridLines(Shader &inShader) {
	unitCube = UnitCube();
	//gridLinesShader =  Shader("res/shaders/baseShader.vert", "res/shaders/baseShader.frag");

	//diffuseMap = inShader.loadTexture("res/images/tile1.png");
	//diffuseMap = inShader.loadTexture("res/images/tile3.png");
	//specularMap = inShader.loadTexture("res/images/brick_spec_map.png");
	
	// shader configuration
	//inShader.setFloat("material.shininess", 32.0f);

	textureOn = true;
}

// USE WITH TILE A

void GridLines::draw(glm::mat4 model, Shader &inShader) {
	
	inShader.use();
	inShader.setBool("borderOn", false);
	inShader.setFloat("specBias", 2.0);
	inShader.setVec3("colour", glm::vec3(0.8f, 0.0f, 0.8f));

	//glActiveTexture(GL_TEXTURE1);
	//glBindTexture(GL_TEXTURE_2D, specularMap);

	// with textureOn use 1 unit cube for better performance (no lag in movement) becuase when off 10 000 unit cubes are generated
	
		// bind texture maps
		glActiveTexture(GL_TEXTURE2);

		model = glm::scale(model, glm::vec3(100.0, 0.1f, 100.0));
		inShader.setMat4("model", model);

		glBindVertexArray(unitCube.getVAO());
		glDrawArrays(GL_TRIANGLES, 0, 36);
		

}

void GridLines::toggleTexture() {

	textureOn = !textureOn;
}