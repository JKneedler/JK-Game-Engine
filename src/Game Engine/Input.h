#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Input {

public:
	Input(GLFWwindow* window);

	bool GetKey(int key);

	GLfloat getXChange();
	GLfloat getYChange();

private:
	bool keys[1024];

	GLfloat lastX, lastY, xChange, yChange;
	bool mouseFirstMoved;

	void createCallbacks(GLFWwindow* window);
	static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);
	static void handleMouse(GLFWwindow* window, double xPos, double yPos);

};

