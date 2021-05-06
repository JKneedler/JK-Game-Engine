#include "Input.h"
#include <stdio.h>

Input::Input(GLFWwindow* window) {
	for (size_t i = 0; i < 1024; i++) {
		keys[i] = 0;
	}

	xChange = 0.0f;
	yChange = 0.0f;

	createCallbacks(window);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Input::createCallbacks(GLFWwindow* window) {
	glfwSetWindowUserPointer(window, this);
	glfwSetKeyCallback(window, handleKeys);
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

