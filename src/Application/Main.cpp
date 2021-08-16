#include "ObjectNode.h"
#include "Transform.h"

#include "../Mesh/unitCube/UnitCube.h"
#include "../Mesh/unitLine/UnitLine.h"
#include "../Models/unitAxes/UnitAxes.h"
#include "../Models/gridLines/GridLines.h"
#include "../Models/lightCube/LightCube.h"
#include "../Models/custom/modelDamian/ModelDamian.h"
#include "../Models/custom/modelElijah/ModelElijah.h"
#include "../Objects/Level.h"
#include "../Objects/Levels/LevelElijah.h"
#include "../Objects/Levels/LevelDamian.h"
#include "../Objects/Levels/LevelThomas.h"
#include "../Mesh/ObjModel.h"
#include "GameManager.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../Shader/stb_image.h"
// Function Prototypes

void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void renderScene(Shader& inShader);
void renderSceneDepth(Shader& inShader);
unsigned int loadTexture(char const* path);
unsigned int loadCubemap(std::vector<std::string> faces);
void renderObjModels(Shader& inShader, ObjModel* inObjArr);

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

// shadows
bool shadows = true;

// -------------------
// INSTANTIATE STATIC VARIABLES (assign memory) for static variable
// -------------------
glm::vec3* Model::colorPalette = new glm::vec3[NUM_COLORS];

GLuint UnitCube::unitCubeVAO = 0;
GLuint UnitCube::unitCubeVBO = 0;

// -------------------
// DECLARE MODELS HERE
// -------------------

// would've called this floor but it's a conflict in a library somewhere (probably GLM)
GridLines* gridLines;
UnitAxes* unitAxes;

Model* activeModel;
ObjectNode* activeNode;

Model* unitCube;

//ModelElijah* modelDamian;

GameManager* game;
ObjectNode* scene;
Level* currentLevel;


LightCube* lightCube;


glm::vec3 cornerCamPos[4];
glm::vec3 boardCamPos;
glm::vec3* currentCamPos;
glm::vec3 focusPoint;

bool camIsFixed = false;
bool centerFocus = true;

bool spotlightOn = true;
bool directionalLightOn = true;
bool ambientLightOn = true;
bool moveSkateboard = false;

int camIndex = 0;



int main()
{
	focusPoint = glm::vec3(0);
	//Camera Positions
	cornerCamPos[0] = glm::vec3(-50, 50, 50);
	cornerCamPos[1] = glm::vec3(50, 50, 50);
	cornerCamPos[2] = glm::vec3(50, 50, -50);
	cornerCamPos[3] = glm::vec3(-45, 45, -45);
	boardCamPos = glm::vec3(0);
	// Initialise GLFW
	if (!glfwInit())
	{
		printf("GLFW initialisation failed");
		glfwTerminate();
		return 1;
	}

	// Setup GLFW window properties
	// OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

	// Core Profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Allow Forward Compatibility
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// Create the window
	GLFWwindow* mainWindow = glfwCreateWindow(windowWidth, windowHeight, "Comp 371 Project: SuperHyperCube Game - Team 7", NULL, NULL);
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

	// configure global opengl state:
	//  -GL_DEPTH_TEST = ensure things behind solid objects are not drawn
	//  -GL_CULL_FACE = ensure that faces of objects not visible are not drawn
	// -----------------------------
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	// Create Viewport
	glViewport(0, 0, windowWidth, windowWidth);

	// ----------------------------------
	// INITIALIZE STATIC VARIABLES
	// ----------------------------------

	Model::setColorPalette();


	// configure depth map FBO
	// -----------------------
	const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
	unsigned int depthMapFBO;
	glGenFramebuffers(1, &depthMapFBO);
	// create depth texture
	unsigned int depthMap;
	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	// attach depth texture as FBO's depth buffer
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);


	// -----------
	// LOAD OBJ MODELS
	// -----------
	ObjModel objArr[]{ObjModel("res/objects/tree7.obj") , ObjModel("res/objects/richierReduced.obj") };

	//-----------
	// Textures
	//-----------

	
	//-----------
	// SHADERS
	//-----------
	Shader shader("res/shaders/baseShader.vert", "res/shaders/baseShader.frag");

	unsigned int diffuseMapBlock  = loadTexture("res/images/brick.png");
	unsigned int diffuseMapWall   = loadTexture("res/images/brick2.jpg");
	unsigned int diffuseMapObject = loadTexture("res/images/metal4.jpg");
	shader.use();
	shader.setInt("diffuseTexture", 0);
	shader.setInt("depthMap", 1);

	Shader depthShader("res/shaders/depthShader.vert","res/shaders/depthShader.frag");

	
	//-----------
	// OBJECTS
	//-----------
	gridLines = new GridLines(shader);

	

	scene = new ObjectNode();
	

	currentLevel = new LevelThomas(shader);
	//currentLevel = new LevelElijah(shader);
	//currentLevel = new LevelDamian(shader);
	
	scene->AddChild(currentLevel);
	currentLevel->AddPosition(glm::vec3(0, 5, 0));
	// skateboard->AddPosition(glm::vec3(0, 2, 0));
	// skateboard->AddChild(board);
	// board->AddScale(glm::vec3(8, -0.7f, 3));
	// skateboard->AddChild(wheel1);
	// 	wheel1->AddPosition(glm::vec3(4,-1,1));
	// skateboard->AddChild(wheel2);
	// 	wheel2->AddPosition(glm::vec3(4, -1, -1));
	// skateboard->AddChild(wheel3);
	// 	wheel3->AddPosition(glm::vec3(-4, -1, 1));
	// skateboard->AddChild(wheel4);
	// 	wheel4->AddPosition(glm::vec3(-4, -1, -1));
	// 	

	
	

	// UNIT AXES / LIGHT CUBE
	unitAxes = new UnitAxes();
	lightCube = new LightCube();

	// ==================================

	// initialize active model
	activeModel = unitCube; //modelRichard;
	activeNode = currentLevel->object;
	
	glm::vec3 lightPos = glm::vec3(-50.0f , 50.0f, -50.0f);

	

	currentCamPos = &cornerCamPos[0];
	
	// display/render loop
	while (!glfwWindowShouldClose(mainWindow))
	{
		boardCamPos = scene->GetPosition() + glm::vec3(0, 1, 0);
		//lightPos = glm::vec3(-10.0f, 10.0f, -10.0f * cos(glfwGetTime()));
		// Get + Handle User Input
		glfwPollEvents();

		// per-frame time logic
		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// input
		processInput(mainWindow);

		//Clear the Window
		glClearColor(0.1f, 0.4f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// 1. render scene to depth texture
		// --------------------------------
		float near_plane = 1.0f; float far_plane = 100.0f;
		
		glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
		glm::mat4  lightView = glm::lookAt(lightPos, glm::vec3(scene->GetPosition()), glm::vec3(0.0, 1.0, 0.0));
				
		glm::mat4 lightSpaceMatrix = lightProjection * lightView;

		depthShader.use();
		depthShader.setMat4("lightSpaceMatrix", lightSpaceMatrix);
		
		glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
		glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
			glClear(GL_DEPTH_BUFFER_BIT);
			
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, diffuseMapObject);
		
		renderObjModels(depthShader, objArr);
		renderSceneDepth(depthShader);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		// 2. render scene as normal 
		// -------------------------
		glViewport(0, 0, windowWidth, windowHeight);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::vec3 forward = scene->getTransform().GetForwardVector();
		forward = glm::normalize(forward);
		glm::vec3 nonCenterFocus = boardCamPos + glm::vec3(forward.x * -10, forward.y * -10, forward.z * -10);

		focusPoint = centerFocus ? glm::vec3(0) : nonCenterFocus;
		
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)windowWidth / (float)windowHeight, 0.1f, 150.0f);
		glm::mat4 view = camIsFixed ? glm::lookAt(*currentCamPos, focusPoint, glm::vec3(0, 1, 0)) : camera.GetViewMatrix();
		
		shader.use();
		shader.setBool("isTextured", false);
		shader.setBool("spotlightOn", spotlightOn);
		shader.setBool("directionalLightOn", directionalLightOn);
		shader.setBool("ambientLightOn", ambientLightOn);
		shader.setVec3("colour", glm::vec3(0.0f, 1.0f, 0.3f));
		shader.setMat4("projection", projection);
		shader.setMat4("view", view);
		// spotlight uniforms
		
		shader.setVec3("spotlight.position", 0,50,0);
		shader.setVec3("spotlight.direction", 0,-10,0);
		shader.setVec3("spotlight.ambient", 0.0f, 0.0f, 0.0f);
		shader.setVec3("spotlight.diffuse", 1.0f, 1.0f, 1.0f);
		shader.setVec3("spotlight.specular", 1.0f, 1.0f, 1.0f);
		shader.setFloat("spotlight.constant", 1.0f);
		shader.setFloat("spotlight.linear", 0.09);
		shader.setFloat("spotlight.quadratic", 0.032);
		shader.setFloat("spotlight.cutOff", glm::cos(glm::radians(12.5f)));
		shader.setFloat("spotlight.outerCutOff", glm::cos(glm::radians(15.0f)));

		// set lighting uniforms
		shader.setVec3("viewPos", camera.Position);
		shader.setVec3("lightPos", lightPos);
		shader.setMat4("lightSpaceMatrix", lightSpaceMatrix);
		glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, diffuseMapObject);
		glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, depthMap);
		glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, diffuseMapWall);

			// glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
			// skyboxShader.use();
			// //view = camera.GetViewMatrix();//glm::mat4(glm::mat3(camera.GetViewMatrix())); // remove translation from the view matrix
			// skyboxShader.setMat4("view", view);
			// skyboxShader.setMat4("projection", projection);
			// // skybox cube
			// glBindVertexArray(skybox->getVAO());
			// glActiveTexture(GL_TEXTURE0);
			// glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
			// //glDrawArrays(GL_TRIANGLES, 0, 36);
			// glBindVertexArray(0);
			// glDepthFunc(GL_LESS); // set depth function back to default

		renderObjModels(shader, objArr);
		renderScene(shader);
		
		// unitAxes and lightCube -- USE DIFFERENT SHADERS -- that's why they're not in the render scene function (also different draw signature)

		unitAxes->draw(camera, projection, view);
		lightCube->draw(projection, view, lightPos);

		scene->Update(deltaTime);

		glfwSwapBuffers(mainWindow);

		
	}

	//delete modelDamian;
	glfwTerminate();
	exit(0);
}

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
	// modelDamian->toggleBorder();
	// modelElijah->toggleBorder();
	// modelThomas->toggleBorder();
	// modelMichael->toggleBorder();
	// modelRichard->toggleBorder();
}

void toggleTextures() {
	// modelDamian->toggleTexture();
	// modelElijah->toggleTexture();
	// modelThomas->toggleTexture();
	// modelMichael->toggleTexture();
	//modelRichard->toggleTexture();

	gridLines->toggleTexture();
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_RELEASE) {
		switch (key) {

			// choose which model is "active" aka which model will be manipulated
		// case GLFW_KEY_0:
		// 	activeModel = unitCube;
		// 	activeNode = scene;
		// 	break;
		// case GLFW_KEY_1:
		// 	activeNode = currentLevel;
		// 	break;
		// case GLFW_KEY_2:
		// 	activeNode = currentLevel->object;
		// 	break;
		case GLFW_KEY_3:

			currentLevel->validateOrientation();
			// Toggle board cam
			// camIsFixed = true;
			// centerFocus = false;
			// currentCamPos = &boardCamPos;
			break;
		case GLFW_KEY_4:
			//Toggle corner cams
			camIsFixed = true;
			centerFocus = true;
			camIndex += 1;
			currentCamPos = &cornerCamPos[camIndex % 4];
			break;
		case GLFW_KEY_5:
			//Toggle Directional Light
			directionalLightOn = !directionalLightOn;
			break;
		case GLFW_KEY_6:
			//Toggle Spotlight
			spotlightOn = !spotlightOn;
			std::cout << "\n spotlight: " << spotlightOn;
			break;
		case GLFW_KEY_7:
			//Toggle Ambient Light
			ambientLightOn = !ambientLightOn;
			break;
		case GLFW_KEY_8:
			moveSkateboard = !moveSkateboard;
			scene->SetPosition(glm::vec3(0));
			// select render mode
		case GLFW_KEY_T:
			activeModel->setRenderMode(GL_TRIANGLES);
			break;
		case GLFW_KEY_P:
			activeModel->setRenderMode(GL_POINTS);
			break;
		case GLFW_KEY_L:
			activeModel->setRenderMode(GL_LINES);
			break;

			// toggle textures
		case GLFW_KEY_X:
			toggleTextures();
			break;


			// scale models up and down
		case GLFW_KEY_U:
			activeNode->AddScale(glm::vec3(0.1, 0.1, 0.1));
			break;

		case GLFW_KEY_J:
			activeNode->AddScale(glm::vec3(-0.1, -0.1, -0.1));
			break;

			// translate models up/down
		case GLFW_KEY_W:
			if (mods == GLFW_MOD_SHIFT)
			{
				//activeModel->translate(TRANS_FORWARD);
				activeNode->AddPosition(glm::vec3(0, 0, -1));//glm::vec3(0, 0, -1));
			}
			else
			{
				activeNode->AddRotation90(glm::vec3(1, 0, 0));
			}
			break;
			
			// translate models left/right and rotate left/right
		case GLFW_KEY_A:

			if (mods == GLFW_MOD_SHIFT) {
				activeNode->AddPosition(glm::vec3(-1, 0, 0));
			}
			else {
				activeNode->AddRotation90(glm::vec3(0, 1, 0));
			}
			break;

		case  GLFW_KEY_S:
			if (mods == GLFW_MOD_SHIFT)
			{
				activeNode->AddPosition(glm::vec3(0, 0, 1));
			}
			else
			{
				activeNode->AddRotation90(glm::vec3(-1, 0, 0));
			}
			break;

		case  GLFW_KEY_D:

			if (mods == GLFW_MOD_SHIFT) {
				activeNode->AddPosition(glm::vec3(1, 0, 0));
			}
			else {
				activeNode->AddRotation90(glm::vec3(0, -1, 0));
			}
			break;
		case GLFW_KEY_Q:
			activeNode->AddRotation90(glm::vec3(0, 0, 1));
			break;
		case GLFW_KEY_E:
			activeNode->AddRotation90(glm::vec3(0, 0, -1));
			break;

		case GLFW_KEY_C:
			//activeModel->toggleContinuous();
			break;

			// rotate along X and Z axis, maybe map y rotation to G and V keys
		case GLFW_KEY_V:
			activeNode->AddRotation(glm::vec3(0.1,0,0));
			break;
		case GLFW_KEY_G:
			activeNode->AddRotation(glm::vec3(-0.1, 0, 0));
			break;
		case GLFW_KEY_H:
			activeNode->AddRotation(glm::vec3(0, 0, 0.1));
			break;
		case GLFW_KEY_B:

			if (mods == GLFW_MOD_SHIFT) {
				toggleBorders();
			}
			else {
				activeNode->AddRotation(glm::vec3(0, 0, -0.1));
			}

			break;

		case GLFW_KEY_HOME:
			camera.sendHome();
			break;

		case GLFW_KEY_R:

			if (mods == GLFW_MOD_SHIFT) {
				
			}
			else {
				//activeModel->generateRandomModel();
			}
			break;

		case GLFW_KEY_O:
			//activeModel->generateOriginalObject();
			break;

		case GLFW_KEY_SPACE:

			if (shadows == true) {
				shadows = false;
			}
			else {
				shadows = true;
			}

			break;

		}
	}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	windowWidth = width;
	windowHeight = height;
}

void renderScene(Shader& inShader)
{
	
	
	gridLines->draw(glm::mat4(1.0f),inShader);

	scene->Draw(inShader);
	// unitCube->draw(model, shader);
	//modelDamian->draw(&inShader);
	//modelElijah->draw(shader);
	//modelThomas->draw(shader);
	//modelMichael->draw(shader);
	//modelRichard->draw(&inShader);
}

void renderSceneDepth(Shader& inShader)
{
	gridLines->draw(glm::mat4(1.0f), inShader);
	scene->Draw(inShader);
	//glCullFace(GL_FRONT);
	// unitCube->draw(model, shader);
	//modelDamian->draw(&inShader);
	//modelElijah->draw(shader);
	//modelThomas->draw(shader);
	//modelMichael->draw(shader);
	//modelRichard->draw(&inShader);
	//glCullFace(GL_BACK);
}

unsigned int loadTexture(char const* path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT); // for this tutorial: use GL_CLAMP_TO_EDGE to prevent semi-transparent borders. Due to interpolation it takes texels from next repeat 
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}

unsigned int loadCubemap(std::vector<std::string> faces)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
			);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_MIRRORED_REPEAT);

	return textureID;
}

void renderObjModels(Shader& inShader, ObjModel* inObjArr) {
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(25.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(-16.0f, 0.0f, -10.0f));
	model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
	inShader.setMat4("model", model);
	inObjArr[0].Draw(inShader);


	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(6.0f, 0.0f, 2.0f));
	inShader.setMat4("model", model);
	inObjArr[1].Draw(inShader);

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(-6.0f, 0.0f, 2.0f));
	model = glm::scale(model, glm::vec3(-1.0f, 1.0f, 1.0f));
	inShader.setMat4("model", model);
	inObjArr[1].Draw(inShader);
}