#pragma once

#include <GLFW/glfw3.h>

class Time {
public:
	Time();
	
	void UpdateDeltaTime();

	static GLfloat deltaTime;

	~Time();

private:
	GLfloat lastTime;
};

