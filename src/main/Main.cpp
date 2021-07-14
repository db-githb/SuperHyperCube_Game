#include "Main.h"
#include "../unitCube/UnitCube.h"
#include "../unitLine/UnitLine.h"
#include "../unitAxes/UnitAxes.h"
#include "../gridLines/GridLines.h"
#include "../modelBase/modelBase.h"
#include "../modelDamian/modelDamian.h"
#include "../modelElijah/modelElijah.h"
#include "../modelThomas/modelThomas.h"

// instantiate camera
Camera camera;

float lastX = WIDTH / 2.0f;
float lastY = HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

ModelBase* activeModel;

// -------------------
// DECLARE MODELS HERE
// -------------------
ModelBase* unitCube;
ModelDamian* modelDamian;
ModelElijah* modelElijah;
ModelThomas* modelThomas;
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

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {

	camera.ProcessMouseScroll((float)yoffset);
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
			}
			else {
				activeModel->rotate(ROTATE_LEFT);
			}
			break;

		case  GLFW_KEY_D:
			if (mods == GLFW_MOD_SHIFT) {
				activeModel->translate(TRANS_RIGHT);
			}
			else {
				activeModel->rotate(ROTATE_RIGHT);
			}
			break;

		// translate models up/down
		case GLFW_KEY_W:
			activeModel->translate(TRANS_UP);
			break;

		case  GLFW_KEY_S:
			activeModel->translate(TRANS_DOWN);
			break;

		case GLFW_KEY_HOME:
			camera.sendHome();
			break;
		
		// change rendering mode
		case  GLFW_KEY_P:
			activeModel->setRenderMode(RENDER_POINTS);
			break;

		case GLFW_KEY_L:
			activeModel->setRenderMode(RENDER_LINES);
			break;

		case GLFW_KEY_T:
			activeModel->setRenderMode(RENDER_TRIANGLES);
			break;
		}
	}
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
	GLFWwindow* mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Test Window", NULL, NULL);
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
	glfwSetScrollCallback(mainWindow, scroll_callback);
	glfwSetMouseButtonCallback(mainWindow, mouse_button_callback);
	glfwSetKeyCallback(mainWindow, key_callback);

	// glad: load all OpenGl function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to intialize GLAD" << std::endl;
		return -1;
	}

	glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// configure global opengl state (GL_DEPTH_TEST = ensure things behind solid objects are not drawn)
	// -----------------------------
	glEnable(GL_DEPTH_TEST);

	// Create Viewport
	glViewport(0, 0, WIDTH, HEIGHT);

	// ----------------------------------
	// INSTANTIATE AND INITIALIZE MODELS HERE
	// ----------------------------------
	UnitAxes unitAxes;
	GridLines gridLines;

	unitCube = new ModelBase();
	unitCube->initialize();

	modelDamian = new ModelDamian();
	modelDamian->initialize();

	modelElijah = new ModelElijah();
	modelElijah->initialize();

	modelThomas = new ModelThomas();
	modelThomas->initialize();


	// ==================================

	// directional lighting values
	glm::vec3 dirLighting[4] = {
		glm::vec3(-0.2f, -1.0f, -0.3f), //direction
		glm::vec3(0.05f, 0.05f, 0.05f), // ambient
		glm::vec3(0.4f, 0.4f, 0.4f), // diffuse
		glm::vec3(0.5f, 0.5f, 0.5f) // specular
	};

	// initialize active model
	activeModel = modelDamian;

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
		//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 model = glm::mat4(1.0f);

		unitAxes.draw(camera, projection, view, model);
		gridLines.draw(camera, projection, view, model);

		// ----------------------------------
		// DRAW MODELS HERE
		// ----------------------------------

		unitCube->draw(camera, dirLighting, projection, view, model);
		modelDamian->draw(camera, dirLighting, projection, view, model);
		modelElijah->draw(camera, dirLighting, projection, view, model);
		modelThomas->draw(camera, dirLighting, projection, view, model);

		// ==================================

		glfwSwapBuffers(mainWindow);
		
	}

	return 0;
}