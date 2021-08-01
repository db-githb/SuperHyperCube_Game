#include "GridLines.h"

GridLines::GridLines(Shader &inShader) {
	unitCube = UnitCube();
	gridLinesShader =  Shader("res/shaders/baseShader.vert", "res/shaders/baseShader.frag");

	diffuseMap = inShader.loadTexture("res/images/tile1.png");
	//diffuseMap = inShader.loadTexture("res/images/tile3.png");
	//specularMap = inShader.loadTexture("res/images/brick_spec_map.png");
	
	// shader configuration
	inShader.use();
	inShader.setInt("material.diffuse", 0);

	//inShader.setFloat("material.shininess", 32.0f);

	textureOn = true;
}

// USE WITH TILE A

void GridLines::draw(glm::mat4 model, Shader &inShader) {
	
	inShader.use();
	
	inShader.setBool("textureOn", textureOn);
	inShader.setBool("borderOn", false);
	inShader.setFloat("specBias", 2.0);
	inShader.setVec3("colour", glm::vec3(0.8f, 0.0f, 0.8f));
	// bind texture maps
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, diffuseMap);

	//glActiveTexture(GL_TEXTURE1);
	//glBindTexture(GL_TEXTURE_2D, specularMap);

	glBindVertexArray(unitCube.getVAO());

	for (float x = -50.0; x < 51; x++) {
		for (float z = -50.0; z < 51; z++) {
			model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(x, 0.0f, z));
			model = glm::scale(model, glm::vec3(1.0, 0.01, 1.0));
			inShader.setMat4("model", model);

			if (textureOn) {
				glDrawArrays(GL_TRIANGLES, 0, 36);
			}
			else {
				glDrawArrays(GL_LINES, 0, 36);
			}
			
		}
	}	
}


//USE WITH TILE3.PNG
/*
void GridLines::draw(glm::mat4 model, Shader &inShader) {

	inShader.use();

	inShader.setBool("textureOn", textureOn);
	inShader.setBool("borderOn", false);
	inShader.setFloat("specBias", 2.0);

	// bind texture maps
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, diffuseMap);

	//	glActiveTexture(GL_TEXTURE1);
	// glBindTexture(GL_TEXTURE_2D, specularMap);

	model = glm::scale(model, glm::vec3(100.0, 0.01, 100.0));	
	inShader.setMat4("model", model);
	glBindVertexArray(unitCube.getVAO());

	glDrawArrays(GL_TRIANGLES, 0, 36);
	
}
*/

void GridLines::toggleTexture() {

	textureOn = !textureOn;
}

void GridLines::pointLightProperties() {
	gridLinesShader.setVec3("pointLight.position", UnitCube::pointLight[POINT_LIGHT_POSITION]);
	gridLinesShader.setVec3("pointLight.ambient", UnitCube::pointLight[POINT_LIGHT_AMBIENT]);
	gridLinesShader.setVec3("pointLight.diffuse", UnitCube::pointLight[POINT_LIGHT_DIFFUSE]);
	gridLinesShader.setVec3("pointLight.specular", UnitCube::pointLight[POINT_LIGHT_SPECULAR]);
	gridLinesShader.setFloat("pointLight.constant", UnitCube::pointLight[POINT_LIGHT_SPECULAR].x);
	gridLinesShader.setFloat("pointLight.linear", UnitCube::pointLight[POINT_LIGHT_SPECULAR].y);
	gridLinesShader.setFloat("pointLight.quadratic", UnitCube::pointLight[POINT_LIGHT_SPECULAR].z);
}