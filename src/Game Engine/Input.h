#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Input {

public:
	Input(GLFWwindow* window);

	void CycleKeys();

	bool GetKey(int key);
	bool GetKeyUp(int key);
	bool GetKeyDown(int key);

	bool GetMouseButton(int button);
	bool GetMouseButtonUp(int button);
	bool GetMouseButtonDown(int button);

	GLfloat getXChange();
	GLfloat getYChange();

private:
	bool keys[1024];
	bool prevKeys[1024];

	bool mouseB[8];
	bool prevMouseB[8];

	GLfloat lastX, lastY, xChange, yChange;
	bool mouseFirstMoved;

	void createCallbacks(GLFWwindow* window);
	static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);
	static void handleMouseButtons(GLFWwindow* window, int button, int action, int mods);
	static void handleMouse(GLFWwindow* window, double xPos, double yPos);

};

