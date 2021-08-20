#pragma once
#include "../unitCube/UnitCube.h"
#include "../unitLine/UnitLine.h"
#include "../unitAxes/UnitAxes.h"
#include "../gridLines/GridLines.h"
#include "../lightCube/LightCube.h"
#include "../gameManager/GameManager.h"
#include "../objModelManager/ObjModelManager.h"
#include "../soundManager/SoundManager.h"
#include "../textGenerator/TextGenerator.h"
#include "../skyCube/SkyCube.h"



// window size
#define WIDTH 1024
#define HEIGHT 768

int windowWidth = WIDTH;
int windowHeight = HEIGHT;

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

GLuint UnitCube::unitCubeVAO = 0;
GLuint UnitCube::unitCubeVBO = 0;

// -------------------
// DECLARE MODELS HERE
// -------------------

GameManager* gameManager;
SoundManager* soundManager;

GridLines* gridLines;
UnitAxes* unitAxes;
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

void toggleBorders() {
	gameManager->activeModel->toggleBorder();
}

void toggleTextures() {
	gameManager->activeModel->toggleTexture();

	gridLines->toggleTexture();
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_RELEASE) {
		switch (key) {
		
		case GLFW_KEY_1:
			soundManager->incMusicVol();
			break;

		case GLFW_KEY_2:
			soundManager->decMusicVol();
			break;

		case GLFW_KEY_0:
			soundManager->muteEffects();
			break;

		case GLFW_KEY_9:
			soundManager->muteMusic();
			break;

		// select render mode
		case GLFW_KEY_T:
			gameManager->activeModel->setRenderMode(GL_TRIANGLES);
			break;

		case GLFW_KEY_P:
			gameManager->activeModel->setRenderMode(GL_POINTS);
			break;
		case GLFW_KEY_L:
			gameManager->activeModel->setRenderMode(GL_LINES);
			break;

		// toggle textures
		case GLFW_KEY_X:
			toggleTextures();
			break;


		// scale models up and down
		case GLFW_KEY_U:
			gameManager->activeModel->scale(SCALE_UP);
			break;

		case GLFW_KEY_J:
			gameManager->activeModel->scale(SCALE_DOWN);
			break;

		// translate models left/right and rotate left/right
		case GLFW_KEY_A:
			soundManager->playRotateSound();
			gameManager->activeModel->rotate(ROTATE_Y_COUNTER);
			break;

		case  GLFW_KEY_D:
			soundManager->playRotateSound();
			gameManager->activeModel->rotate(ROTATE_Y_CLOCKWISE);
			break;

		// translate models up/down
		case GLFW_KEY_S:
			soundManager->playRotateSound();
			gameManager->activeModel->rotate(ROTATE_X_CLOCKWISE);
			break;

		case  GLFW_KEY_W:
			soundManager->playRotateSound();
			gameManager->activeModel->rotate(ROTATE_X_COUNTER);
			break;

		case GLFW_KEY_HOME:
			camera.sendHome();
			break;

		case GLFW_KEY_R:
			gameManager->activeModel->resetPOS();
			break;

		case GLFW_KEY_SPACE:
			gameManager->start();
			break;

		case GLFW_KEY_ENTER:
			gameManager->speedUp();
			break;
		}
	}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	windowWidth = width;
	windowHeight = height;
	gameManager->setWindowSize((float)width, (float)height);
}

void renderScene(Shader &inShader, bool shadowMap) {
	glm::mat4 model = glm::mat4(1.0f);
	
	gridLines->draw(model, inShader);

	Shader* shader = nullptr;
	
	if (shadowMap) {
		shader = &inShader;
	}
	gameManager->draw(shader);
}

int main()
{

	// seed rand function
	srand((int)(glfwGetTime() * 1000000.0f) % 1000);

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
	GLFWwindow* mainWindow = glfwCreateWindow(windowWidth, windowHeight, "Comp 371: SuperHyperCube Project - Team 7", NULL, NULL);
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
	glfwSetFramebufferSizeCallback(mainWindow, framebuffer_size_callback);

	// glad: load all OpenGl function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to intialize GLAD" << std::endl;
		return -1;
	}

	// tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
	stbi_set_flip_vertically_on_load(true);

	//glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// configure global opengl state:
	//  -GL_DEPTH_TEST = ensure things behind solid objects are not drawn
	//  -GL_CULL_FACE = ensure that faces of objects not visible are not drawn
	// -----------------------------
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Create Viewport
	glViewport(0, 0, windowWidth, windowWidth);

	// ----------------------------------
	// INITIALIZE STATIC VARIABLES
	// ----------------------------------

	ModelBase::setColorPalette();


	// configure depthMap FBO
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

	//-----------
	// SHADERS
	//-----------
	Shader shader("res/shaders/baseShader.vert", "res/shaders/baseShader.frag");
	Shader shadowMapShader("res/shaders/shadowMapShader.vert", "res/shaders/shadowMapShader.frag", "res/shaders/shadowMapShader.geom");
	Shader textShader("res/shaders/textShader.vert", "res/shaders/textShader.frag");

	//-----------
	// OBJECTS
	//-----------
	gridLines = new GridLines(shader);

	TextGenerator textGenerator = TextGenerator();
	textGenerator.setup();

	//start sound manager
	soundManager = new SoundManager();
	soundManager->muteMusic();

	//start game manager
	gameManager = new GameManager();
	gameManager->initialize(&shader, &textShader, soundManager, glm::vec2(windowWidth, windowHeight));

	//start .obj model manager
	ObjModelManager objModelManager = ObjModelManager();

	// UNIT AXES / LIGHT CUBE / SKY CUBE
	unitAxes = new UnitAxes();
	lightCube = new LightCube();
	SkyCube skyCube = SkyCube();
	// ==================================

	// display/render loop
	while (!glfwWindowShouldClose(mainWindow))
	{
		// Get + Handle User Input
		glfwPollEvents();

		// per-frame time logic
		float currentFrame = (float) glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// input
		processInput(mainWindow);

		//Clear the Window
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glm::vec3 lightPos = gameManager->activeModel->modelBasePosition + glm::vec3(5.0f, 20.5f, -5.0f);

		// 0. create depth cubemap transformation matrices
		// -----------------------------------------------
		
		// when 30 < far_plane shadow acne appears
		// when far_plane < 100 spotlight effect occurs
		// Note: near_plane and far_plane only used in shadow mapping (far_plane passed to frag shader)
		float near_plane = 1;
		float far_plane = 100.0;
		
		glm::mat4 shadowProj = glm::perspective(glm::radians(90.0f), (float)SHADOW_WIDTH / (float)SHADOW_HEIGHT, near_plane, far_plane);

		// lightSpace matrix produced by the shadowProjection matrix and the lookAt view matrix
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

		objModelManager.renderObjModels(shader, true);
		renderScene(shadowMapShader, true);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		
		// 2. render scene as normal 
		// -------------------------
		glViewport(0, 0, windowWidth, windowHeight);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(windowWidth), 0.0f, static_cast<float>(windowHeight));
		textShader.use();
		textShader.setMat4("projection", projection);

		shader.use();
		projection = glm::perspective(glm::radians(camera.Zoom), (float)windowWidth / (float)windowHeight, 0.1f, 200.0f);
		glm::mat4 view = camera.GetViewMatrix();
		shader.setMat4("projection", projection);
		shader.setMat4("view", view);

		// set lighting uniforms
		shader.setVec3("pointLight.position", lightPos);
		shader.setVec3("viewPos", camera.Position);
		shader.setFloat("far_plane", far_plane);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubemap);
		
		objModelManager.renderObjModels(shader, false);
		renderScene(shader, false);
		
		// unitAxes and lightCube -- USE DIFFERENT SHADERS -- that's why they're not in the render scene function (also different draw signature)
		//unitAxes->draw(camera, projection, view);
		//lightCube->draw(projection, view, lightPos);
		skyCube.draw(projection, view);

		glfwSwapBuffers(mainWindow);
	}

	glfwTerminate();
	exit(0);
}