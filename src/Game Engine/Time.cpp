#include "Time.h"

GLfloat Time::deltaTime{ 0.0f };

Time::Time() {
	deltaTime = 0.0f;
	lastTime = 0.0f;
}

void Time::UpdateDeltaTime() {
	GLfloat now = glfwGetTime();
	deltaTime = now - lastTime;
	lastTime = now;
}

Time::~Time() {
}
