#include "Input.h"
#include <stdio.h>

Input::Input(GLFWwindow* window) {
	for (size_t i = 0; i < 1024; i++) {
		keys[i] = 0;
		prevKeys[i] = 0;
	}

	for (size_t i = 0; i < 8; i++) {
		mouseB[i] = 0;
		prevMouseB[i] = 0;
	}

	xChange = 0.0f;
	yChange = 0.0f;

	createCallbacks(window);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Input::CycleKeys() {
	for (size_t i = 0; i < 1024; i++) {
		prevKeys[i] = keys[i];
	}
	for (size_t i = 0; i < 8; i++) {
		prevMouseB[i] = mouseB[i];
	}
}

void Input::createCallbacks(GLFWwindow* window) {
	glfwSetWindowUserPointer(window, this);
	glfwSetKeyCallback(window, handleKeys);
	glfwSetMouseButtonCallback(window, handleMouseButtons);
	glfwSetCursorPosCallback(window, handleMouse);
}

void Input::handleKeys(GLFWwindow* window, int key, int code, int action, int mode) {
	//This needs to be replaced by just a way to get the main Input within the EngineManager
	Input* input = static_cast<Input*>(glfwGetWindowUserPointer(window));

	//Change later when there is an actual exit button. That way won't accidentally close by pressing escape
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024) {
		if (action == GLFW_PRESS) {
			input->keys[key] = true;
		}
		else if (action == GLFW_RELEASE) {
			input->keys[key] = false;
		}
	}
}

void Input::handleMouseButtons(GLFWwindow* window, int button, int action, int mods) {
	//This needs to be replaced by just a way to get the main Input within the EngineManager
	Input* input = static_cast<Input*>(glfwGetWindowUserPointer(window));

	if (button >= 0 && button < 8) {
		if (action == GLFW_PRESS) {
			input->mouseB[button] = true;
		}
		else if (action == GLFW_RELEASE) {
			input->mouseB[button] = false;
		}
	}
}

void Input::handleMouse(GLFWwindow* window, double xPos, double yPos) {
	Input* input = static_cast<Input*>(glfwGetWindowUserPointer(window));

	if (input->mouseFirstMoved) {
		input->lastX = xPos;
		input->lastY = yPos;
		input->mouseFirstMoved = false;
	}

	input->xChange = xPos - input->lastX;
	input->yChange = input->lastY - yPos;

	input->lastX = xPos;
	input->lastY = yPos;
}

bool Input::GetKey(int key) {
	return keys[key];
}

bool Input::GetKeyUp(int key) {
	return !keys[key] && prevKeys[key];
}

bool Input::GetKeyDown(int key) {
	return keys[key] && !prevKeys[key];
}

bool Input::GetMouseButton(int button) {
	return mouseB[button];
}

bool Input::GetMouseButtonUp(int button) {
	return !mouseB[button] && prevMouseB[button];
}

bool Input::GetMouseButtonDown(int button) {
	return mouseB[button] && !prevMouseB[button];
}

GLfloat Input::getXChange() {
	GLfloat theChange = xChange;
	xChange = 0;
	return theChange;
}

GLfloat Input::getYChange() {
	GLfloat theChange = yChange;
	yChange = 0;
	return theChange;
}

