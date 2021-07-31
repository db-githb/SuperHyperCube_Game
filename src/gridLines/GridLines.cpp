#include "GridLines.h"

GridLines::GridLines() {
	UnitCube unitCube= UnitCube();
	gridLinesShader =  Shader("res/shaders/baseShader.vert", "res/shaders/baseShader.frag");

	//diffuseMap = gridLinesShader.loadTexture("res/images/tile_a.png");
	diffuseMap = gridLinesShader.loadTexture("res/images/tile3.png");
	specularMap = gridLinesShader.loadTexture("res/images/brick_spec_map.png");
	
	// shader configuration
	gridLinesShader.use();
	gridLinesShader.setInt("material.diffuse", 0);

	gridLinesShader.setFloat("material.shininess", 32.0f);
}

// USE WITH TILE A
/*
void GridLines::draw(Camera inCam, glm::mat4 projection, glm::mat4 view, glm::mat4 model) {
	
	gridLinesShader.use();
	pointLightProperties();
	gridLinesShader.setMat4("projection", projection);
	gridLinesShader.setMat4("view", view);

	gridLinesShader.setVec3("viewPos", inCam.Position);;
	
	// bind texture maps
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, diffuseMap);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, specularMap);

	glBindVertexArray(unitCube.getVAO());

	for (float x = -50.0; x < 51; x++) {
		for (float z = -50.0; z < 51; z++) {
			model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(x, 0.0f, z));
			model = glm::scale(model, glm::vec3(1.0, 0.01, 1.0));
			gridLinesShader.setMat4("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
	}	
}
*/

//USE WITH TILE3.PNG
void GridLines::draw(Camera inCam, glm::mat4 projection, glm::mat4 view, glm::mat4 model, const Shader &shadowMapShader) {

	gridLinesShader.use();
	pointLightProperties();

	gridLinesShader.setMat4("projection", projection);
	gridLinesShader.setMat4("view", view);

	gridLinesShader.setVec3("viewPos", inCam.Position);

	model = glm::scale(model, glm::vec3(100.0, 0.01, 100.0));

	if (&shadowMapShader == NULL) {
		gridLinesShader.setMat4("model", model);
	}
	else {
		shadowMapShader.setMat4("model", model);
	}
	

	// bind texture maps
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, diffuseMap);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, specularMap);

	glBindVertexArray(unitCube.getVAO());

	glDrawArrays(GL_TRIANGLES, 0, 36);
	
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