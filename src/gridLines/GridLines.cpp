#include "GridLines.h"

GridLines::GridLines() {
	UnitCube unitCube= UnitCube();
	gridLinesShader =  Shader("res/shaders/cubeShader.vert", "res/shaders/cubeShader.frag");

	//diffuseMap = gridLinesShader.loadTexture("res/images/tile.jpg");
	diffuseMap = gridLinesShader.loadTexture("res/images/tile3.png");
	// shader configuration
	gridLinesShader.use();
	gridLinesShader.setInt("material.diffuse", 0);

	// light properties
	gridLinesShader.setVec3("dirLight.direction", UnitCube::dirLight[LIGHT_DIRECTION]);
	gridLinesShader.setVec3("dirLight.ambient", UnitCube::dirLight[LIGHT_AMBIENT]);
	gridLinesShader.setVec3("dirLight.diffuse", UnitCube::dirLight[LIGHT_DIFFUSE]);
	gridLinesShader.setVec3("dirLight.specular", UnitCube::dirLight[LIGHT_SPECULAR]);

	// material properties
	gridLinesShader.setVec3("material.specular", 0.5f, 0.5f, 0.5f);
	gridLinesShader.setFloat("material.shininess", 64.0f);
}
/*
void GridLines::draw(Camera inCam, glm::mat4 projection, glm::mat4 view, glm::mat4 model) {
	
	gridLinesShader.use();
	gridLinesShader.setMat4("projection", projection);
	gridLinesShader.setMat4("view", view);

	gridLinesShader.setVec3("viewPos", inCam.Position);;
	
	// bind texture maps
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, diffuseMap);

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
void GridLines::draw(Camera inCam, glm::mat4 projection, glm::mat4 view, glm::mat4 model) {

	gridLinesShader.use();
	gridLinesShader.setMat4("projection", projection);
	gridLinesShader.setMat4("view", view);

	gridLinesShader.setVec3("viewPos", inCam.Position);

	model = glm::scale(model, glm::vec3(100.0, 0.01, 100.0));
	gridLinesShader.setMat4("model", model);

	// bind texture maps
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, diffuseMap);

	glBindVertexArray(unitCube.getVAO());

	glDrawArrays(GL_TRIANGLES, 0, 36);

}
