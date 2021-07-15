#ifndef CAMERA_H
#define CAMERA_H

#include "../../glad/glad.h"
#include "../../glm/glm.hpp"
#include "../../glm/gtc/matrix_transform.hpp"

#include <vector>

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

enum Mouse_Button {
	None,
	Right,
	Middle,
	Left
};

#define HOME_POSITION glm::vec3(0.0f, 15.0f, 25.0f)
#define HOME_YAW -90.0f
#define HOME_PITCH -35.0f
#define HOME_UP glm::vec3(0.0f, 1.0f, 0.0f)


// Default camera values
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera
{
public:
	// camera Attributes
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up; //  TODO: check what this parameter does.  Pretty sure we only need to the worldUp parameter
	glm::vec3 Right;
	glm::vec3 WorldUp;

	// euler Angles
	float Yaw;
	float Pitch;

	// camera options
	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;

	Mouse_Button Engaged;

	// constructor with vectors
	Camera(glm::vec3 position = HOME_POSITION, glm::vec3 up = HOME_UP, float yaw = HOME_YAW, float pitch = HOME_PITCH);

	// constructor with scalar values
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

	void sendHome();

	// returns the view matrix calculated using Euler Angles and the LookAt Matrix
	glm::mat4 GetViewMatrix();

	// processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
	void ProcessKeyboard(Camera_Movement direction, float deltaTime);

	// processes input received from a mouse input system. Expects the offset value in both the x and y direction.
	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);

	// processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
	void ProcessMouseScroll(float yoffset);

private:
	// calculates the front vector from the Camera's (updated) Euler Angles
	void updateCameraVectors();
};
#endif
