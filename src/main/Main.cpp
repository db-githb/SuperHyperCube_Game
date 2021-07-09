#include "Main.h"

void createCubes()
{
	float vertices[] = {
		// positions          // normals        // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f, 0.0f, 0.0f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f, 0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f, 0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f, 0.0f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f, 0.0f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f, 0.0f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f, 0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f, 0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f, 0.0f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f, 0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f, 0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f, 0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f, 0.0f,  0.0f, 1.0f
	};

	// lightCube VAO and VBO
	glGenVertexArrays(1, &letterCubeVAO);

	glGenBuffers(1, &letterCubeVBO);
	glBindBuffer(GL_ARRAY_BUFFER, letterCubeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(letterCubeVAO);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//unbind VBO 
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//unbind VAO
	glBindVertexArray(0);
}

void createLine()
{
	
	float vertices[] = {
		// position      
		0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f
	};

	// line VAO and VBO
	glGenVertexArrays(1, &lineVAO);

	glGenBuffers(1, &lineVBO);
	
	glBindBuffer(GL_ARRAY_BUFFER, lineVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(lineVAO);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
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
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		return;
	}

	return;

}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
		return;
	}
	return;
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

	createCubes();
	createLine();

	// positions of the cubses
	glm::vec3 cubePositions[] =
	{
		glm::vec3(-1.0f,  0.5f,  -2.0f),
	};

	// damian outer model positions


	// grid line positions
	glm::vec3 gridLinePositions[128];
	for (int i = 0; i < 100; i++) {
		gridLinePositions[i] = glm::vec3(-50.0 + (float)i,  0.0f,  0.0f);
	}

	// compile shaders
	Shader cubeShader("res/shaders/cubeShader.vert", "res/shaders/cubeShader.frag");
	Shader axisShader("res/shaders/axisShader.vert", "res/shaders/axisShader.frag");
	Shader gridLineShader("res/shaders/gridLineShader.vert", "res/shaders/gridLineShader.frag");

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

		//--------------
		// UNIT CUBE
		//--------------

		cubeShader.use();

		cubeShader.setVec3("viewPos", camera.Position);
		//letterCubeShader.setFloat("material.shininess", 32.0f);

		cubeShader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
		cubeShader.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
		cubeShader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
		cubeShader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);

		// view/projection transformations
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		cubeShader.setMat4("projection", projection);
		cubeShader.setMat4("view", view);

		// world transformation
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, cubePositions[0]);
		cubeShader.setMat4("model", model);

		// render the cubes
		glBindVertexArray(letterCubeVAO);

		glDrawArrays(GL_TRIANGLES, 0, 36);


		//----------------
		// DAMIAN MODEL
		//---------------



		//-----------
		// UNIT AXIS
		//-----------

		axisShader.use();
		axisShader.setMat4("projection", projection);
		axisShader.setMat4("view", view);
		model = glm::mat4(1.0f);
		for (int i = 0; i < 3; i++) {

			switch (i) {
			case 0:
				axisShader.setInt("xAxis", 1);
				axisShader.setVec3("color", glm::vec3(1.0, 0.0, 0.0));
				break;

			case 1:
				model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
				axisShader.setInt("yAxis", 1);
				axisShader.setVec3("color", glm::vec3(0.0, 1.0, 0.0));
				break;

			case 2:
				model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
				axisShader.setInt("zAxis", 1);
				axisShader.setVec3("color", glm::vec3(0.0, 0.0, 1.0));
				break;
			}

			axisShader.setMat4("model", model);
			glBindVertexArray(lineVAO);
			glDrawArrays(GL_LINES, 0, 2);

		}
		
		//-------------
		// GRID LINES 
		//-------------

		gridLineShader.use();
		gridLineShader.setMat4("projection", projection);
		gridLineShader.setMat4("view", view);

		// lines parallel to z-axis
		for (int i = 0; i < 100; i++) {
			model = glm::scale(glm::mat4(1.0f), glm::vec3(0.2f));
			model = glm::translate(model, gridLinePositions[i]);
			model = glm::translate(model, glm::vec3(0.0f, 0.0f, 50.0f));
			model = glm::scale(model, glm::vec3(100.0f, 100.0f, 100.0f));
			model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			gridLineShader.setMat4("model", model);
			glBindVertexArray(lineVAO);
			glDrawArrays(GL_LINES, 0, 2);
		}

		// lines perpendicular to z-axis
		for (int i = 0; i < 100; i++) { 
			model = glm::scale(glm::mat4(1.0f), glm::vec3(0.2f));
			model = glm::translate(model, glm::vec3(0.0f, 0.0f, gridLinePositions[i].x));
			model = glm::translate(model, glm::vec3(-50.0f, 0.0f, 0.0f));
			model = glm::scale(model, glm::vec3(100.0f, 100.0f, 100.0f));
			gridLineShader.setMat4("model", model);
			glBindVertexArray(lineVAO);
			glDrawArrays(GL_LINES, 0, 2);
		}

		glfwSwapBuffers(mainWindow);
		
	}
	return 0;
}