#include "../unitCube/UnitCube.h"
#include "../unitLine/UnitLine.h"
#include "../unitAxes/UnitAxes.h"
#include "../gridLines/GridLines.h"
//#include "../modelBase/modelBase.h"
#include "../modelDamian/modelDamian.h"
#include "../modelElijah/modelElijah.h"
#include "../modelThomas/modelThomas.h"
#include "../modelMichael/modelMichael.h"
#include "../lightCube/LightCube.h"

// -------------------
// BUILDS WITHOUT INCLUDING MODEL BASE????
// -------------------

// window size
#define WIDTH 1024
#define HEIGHT 768

// instantiate camera
Camera camera;

float lastX = WIDTH / 2.0f;
float lastY = HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// -------------------
// INSTANTIATE STATIC VARIABLES (assign memory) for static variable
// -------------------
glm::vec3* ModelBase::colorPalette = new glm::vec3[NUM_COLORS];
glm::vec3* UnitCube::pointLight = new glm::vec3[5];

GLuint UnitCube::unitCubeVAO = 0;
GLuint UnitCube::unitCubeVBO = 0;

// -------------------
// DECLARE MODELS HERE
// -------------------
UnitAxes* unitAxes;
GridLines* gridLines;

ModelBase* activeModel;
ModelBase* unitCube;
ModelDamian* modelDamian;
ModelElijah* modelElijah;
ModelThomas* modelThomas;
ModelMichael* modelMichael;

LightCube* lightCube;
// ===================

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		camera.ProcessKeyboard(Camera_Movement::FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		camera.ProcessKeyboard(Camera_Movement::BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		camera.ProcessKeyboard(Camera_Movement::LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		camera.ProcessKeyboard(Camera_Movement::RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		camera.ProcessKeyboard(Camera_Movement::UP, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		camera.ProcessKeyboard(Camera_Movement::DOWN, deltaTime);

}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {

	if (firstMouse)
	{
		lastX = (float)xpos;
		lastY = (float)ypos;
		firstMouse = false;
	}

	float xoffset = (float)xpos - lastX;
	float yoffset = lastY - (float)ypos; // reversed since y-coordinates go from bottom to top

	lastX = (float)xpos;
	lastY = (float)ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{
		camera.Engaged = Mouse_Button::Right;
		return;
	}
	if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS)
	{
		camera.Engaged = Mouse_Button::Middle;
		return;
	}
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		camera.Engaged = Mouse_Button::Left;
		return;
	}
	camera.Engaged = Mouse_Button::None;
	return;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_RELEASE) {
		switch (key) {

		// choose which model is "active" aka which model will be manipulated
		case GLFW_KEY_0:
			activeModel = unitCube;
			break;
		case GLFW_KEY_1:
			activeModel = modelDamian;
			break;
		case GLFW_KEY_2:
			activeModel = modelElijah;
			break;
		case GLFW_KEY_3:
			activeModel = modelThomas;
			break;
		case GLFW_KEY_4:
			activeModel = modelMichael;
			break;

		// select render mode
		case GLFW_KEY_T:
			activeModel->setRenderMode(GL_TRIANGLES);
			break;
		case GLFW_KEY_P:
			activeModel->setRenderMode(GL_POINTS);
			break;
		case GLFW_KEY_L:
			activeModel->setRenderMode(GL_LINES);


		// scale models up and down
		case GLFW_KEY_U:
			activeModel->scale(SCALE_UP);
			break;

		case GLFW_KEY_J:
			activeModel->scale(SCALE_DOWN);
			break;

		// translate models left/right and rotate left/right
		case GLFW_KEY_A:

			if (mods == GLFW_MOD_SHIFT) {
				activeModel->translate(TRANS_LEFT);

				// if boundary collision occurs undo left translation
				/*
				if (activeModel->boundaryCollision()) {
					activeModel->translate(TRANS_RIGHT);
				}
				*/
			}
			else {
				activeModel->rotate(ROTATE_Y_COUNTER);

				// if boundary collision occurs undo left rotation
				/*
				if (activeModel->boundaryCollision()) {
					activeModel->rotate(ROTATE_RIGHT);
				}
				*/
			}
			break;

		case  GLFW_KEY_D:

			if (mods == GLFW_MOD_SHIFT) {
				activeModel->translate(TRANS_RIGHT);

				// if boundary collision occurs undo right translation
				/*
				if (activeModel->boundaryCollision()) {
					activeModel->translate(TRANS_LEFT);
				}
				*/
			}
			else {
				activeModel->rotate(ROTATE_Y_CLOCKWISE);

				// if boundary collision occurs undo right rotation
				/*
				if (activeModel->boundaryCollision()) {
					activeModel->rotate(ROTATE_LEFT);
				}
				*/
			}
			break;

		// translate models up/down
		case GLFW_KEY_W:
			activeModel->translate(TRANS_UP);
			return;

		case  GLFW_KEY_S:
			/*
			if (activeModel->boundaryCollision()) {
				return;
			}
			*/
			activeModel->translate(TRANS_DOWN);
			break;

		case GLFW_KEY_Z:
			activeModel->translate(TRANS_FORWARD);
			break;

		case GLFW_KEY_X:
			activeModel->translate(TRANS_BACKWARD);
			break;

		// rotate along X and Z axis, maybe map y rotation to G and V keys
		case GLFW_KEY_F:
			activeModel->rotate(ROTATE_X_CLOCKWISE);
			break;
		case GLFW_KEY_C:
			activeModel->rotate(ROTATE_X_COUNTER);
			break;
		case GLFW_KEY_H:
			activeModel->rotate(ROTATE_Z_CLOCKWISE);
			break;
		case GLFW_KEY_B:
			activeModel->rotate(ROTATE_Z_COUNTER);
			break;

		case GLFW_KEY_HOME:
			camera.sendHome();
			break;

		case GLFW_KEY_R:
			activeModel->generateRandomModel();
			break;

		case GLFW_KEY_O:
			activeModel->generateOriginalObject();
			break;
		}
	}
}

void renderScene(glm::mat4 projection, glm::mat4 view, Shader *shader) {

	//glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
	//glm::mat4 view = camera.GetViewMatrix();
	glm::mat4 model = glm::mat4(1.0f);

	glm::vec3 activeLightPosition = activeModel->modelBasePosition + glm::vec3(0.0f, 1.5f, -2.0f);
	UnitCube::pointLight[POINT_LIGHT_POSITION] = activeLightPosition;

	unitAxes->draw(camera, projection, view, model);
	//gridLines->draw(camera, projection, view, model, *shader);

	// ----------------------------------
	// DRAW MODELS HERE
	// ----------------------------------
	lightCube->draw(projection, view, model,activeLightPosition);
	//modelDamian->draw(camera, projection, view, model, *shader);
	//modelElijah->draw(camera, projection, view, model, *shader);
	//modelThomas->draw(camera, projection, view, model, *shader);
	//modelMichael->draw(camera, projection, view, model, *shader);

	//unitCube->draw(camera, projection, view, model, *shader);
	// ==================================
}

int main()
{
	// Initialise GLFW
		if (!glfwInit())
		{
			printf("GLFW initialisation failed");
			glfwTerminate();
			return 1;
		}

	// Setup GLFW window properties
	// OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// Core Profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Allow Forward Compatibility
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// Create the window
	GLFWwindow* mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Comp 371: Assignment 1 - Team 7", NULL, NULL);
	if (!mainWindow)
	{
		printf("GLFW window creation failed!");
		glfwTerminate();
		return 1;
	}

	// Get Buffer Size information
	int bufferWidth, bufferHeight;
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	// Set context for GLAD to use
	glfwMakeContextCurrent(mainWindow);
	glfwSetCursorPosCallback(mainWindow, mouse_callback);
	glfwSetMouseButtonCallback(mainWindow, mouse_button_callback);
	glfwSetKeyCallback(mainWindow, key_callback);

	// glad: load all OpenGl function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to intialize GLAD" << std::endl;
		return -1;
	}

	glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// configure global opengl state:
	//  -GL_DEPTH_TEST = ensure things behind solid objects are not drawn
	//  -GL_CULL_FACE = ensure that faces of objects not visible are not drawn
	// -----------------------------
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);

	// Create Viewport
	glViewport(0, 0, WIDTH, HEIGHT);

	// ----------------------------------
	// INITIALIZE STATIC VARIABLES
	// ----------------------------------

	
	
	//unsigned int specularMap = shader.loadTexture("res/images/brick_spec_map.png");

	// ----------------------------------
	// INSTANTIATE AND INITIALIZE MODELS HERE
	// ----------------------------------

	
	//gridLines = new GridLines(shader);
	
	
	//unitCube = new ModelBase();
	//unitCube->initialize();

	//modelDamian = new ModelDamian();
	//modelDamian->initialize();

	//modelElijah = new ModelElijah();
	//modelElijah->initialize();

	//modelThomas = new ModelThomas();
	//modelThomas->initialize();

	//modelMichael = new ModelMichael();
	//modelMichael->initialize();

	// ==================================

	// initialize active model
	//activeModel = unitCube; // modelDamian;
	//glm::vec3 lightPos = activeModel->modelBasePosition + glm::vec3(0.0f, 1.5f, -2.0f);

	// configure depth map FBO
  // -----------------------
	const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
	unsigned int depthMapFBO;
	glGenFramebuffers(1, &depthMapFBO);
	// create depth cubemap texture
	unsigned int depthCubemap;
	glGenTextures(1, &depthCubemap);
	glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubemap);
	for (unsigned int i = 0; i < 6; ++i) {
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	}
		
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	// attach depth texture as FBO's depth buffer
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthCubemap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// UNIT AXES / LIGHT CUBE
	unitAxes = new UnitAxes();
	lightCube = new LightCube();

	// SHADERS
	Shader shader("res/shaders/baseShader.vert", "res/shaders/baseShader.frag");
	
	unsigned int diffuseMapBlock = shader.loadTexture("res/images/brick.png");
	shader.use();
	shader.setInt("material.diffuse", 0);
	shader.setInt("depthMap", 1);

	Shader shadowMapShader("res/shaders/shadowMapShader.vert", "res/shaders/shadowMapShader.frag", "res/shaders/shadowMapShader.geom");

	// OBJECTS
	GridLines floor(shader);

	glm::vec3 lightPos = glm::vec3(0.0f, 1.5f, -2.0f);

	// display/render loop
	while (!glfwWindowShouldClose(mainWindow))
	{

		// per-frame time logic
		float currentFrame = (float) glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// input
		processInput(mainWindow);

		//Clear the Window
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// 0. create depth cubemap transformation matrices
	  // -----------------------------------------------
		
		float near_plane = 1;
		float far_plane = 25.0;
		
		glm::mat4 shadowProj = glm::perspective(glm::radians(90.0f), (float)SHADOW_WIDTH / (float)SHADOW_HEIGHT, near_plane, far_plane);
		std::vector<glm::mat4> shadowTransforms;
		shadowTransforms.push_back(shadowProj* glm::lookAt(lightPos, lightPos + glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
		shadowTransforms.push_back(shadowProj* glm::lookAt(lightPos, lightPos + glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
		shadowTransforms.push_back(shadowProj* glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
		shadowTransforms.push_back(shadowProj* glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)));
		shadowTransforms.push_back(shadowProj* glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
		shadowTransforms.push_back(shadowProj* glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
		
		// 1. render scene to depth cubemap
		// --------------------------------
		glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
		glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
		glClear(GL_DEPTH_BUFFER_BIT);
		shadowMapShader.use();
		for (unsigned int i = 0; i < 6; ++i)
			shadowMapShader.setMat4("shadowMatrices[" + std::to_string(i) + "]", shadowTransforms[i]);
		shadowMapShader.setFloat("far_plane", far_plane);
		shadowMapShader.setVec3("lightPos", lightPos);

		// render scene
		glm::mat4 model = glm::mat4(1.0f);
		//floor
		floor.draw(model, shadowMapShader);

		// unit cube
		UnitCube unitCube = UnitCube();
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0, 0.5, 0.0));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		shadowMapShader.setMat4("model", model);
		glBindVertexArray(unitCube.getVAO());
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	

		// 2. render scene as normal 
		// -------------------------
		glViewport(0, 0, WIDTH, HEIGHT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shader.use();
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		shader.setMat4("projection", projection);
		shader.setMat4("view", view);
		// set lighting uniforms
		shader.setVec3("pointLight.position", lightPos);
		shader.setVec3("viewPos", camera.Position);
		//shader.setInt("shadows", 0); // enable/disable shadows by pressing 'SPACE'
		shader.setFloat("far_plane", far_plane);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubemap);



		// render scene
		model = glm::mat4(1.0f);

		//floor
		floor.draw(model, shader);

		// unitAxes and lightCube -- THEY USE DIFFERENT SHADERS
		unitAxes->draw(camera, projection, view, model);
		lightCube->draw(projection, view, model, lightPos);


		// unit cube
		shader.use();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseMapBlock);
		model = glm::mat4(1.0f);
		model=glm::translate(model, glm::vec3(0.0, 0.5, 0.0));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		shader.setMat4("model", model);
		glBindVertexArray(unitCube.getVAO());
		glDrawArrays(GL_TRIANGLES, 0, 36);
		
		//unitCube->draw(model, shader);

		glfwSwapBuffers(mainWindow);
		
		// Get + Handle User Input
		glfwPollEvents();
	}

	delete modelDamian;
	glfwTerminate();
	exit(0);
}