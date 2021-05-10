# JK-Game-Engine
C++ Game Engine made with OpenGL
## How to Use
* Create new solution with JK-Game-Engine and a new project set to output an .exe
* add include directories for GLEW, GLFW, glm, ASSIMP, and the JK-Game-Engine src directory
* add library directories for GLEW, GLFW and ASSIMP
* add dependencies for opengl, glew, glfw, and assimp
* `#include "JKGE.h"` to link header files to main.cpp file in game project

### main.cpp in game project
```
#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>

// Main include that contains all header files for JK-Game-Engine
#include "JKGE.h"

EngineManager* engine;

int main() {
	engine = engine->getInstance();
	engine->Initialize(1920, 1080);
	
	Scene* scene1;
  // Add GameObjects, shaders, and lights to scene1
	engine->getSceneM()->LoadScene(scene1);

	engine->Start();

	// --------- Test Initial Code -----------

	// --------- End Test Initial Code ----------

	while (!engine->getWindowM()->getShouldClose()) {

		// --------- Test Code -----------

		// --------- End Test Code ---------

		engine->Update();

	}
}
```


## About

![Sandbox 2021-05-10 11-14-05-49 (4)](https://user-images.githubusercontent.com/25457814/117694592-51741800-b18d-11eb-9d25-1a2e5a02c580.gif)
### This project is a work in progress - Next Steps
* Omnidirectional Shadows
* Custom Scene file format - allow for loading of scene by file instead of hardcoding
* Asset Memory Management outside of the Scene
* Expand Model Importing for GameObject Component System
* Collision Detection + Rigidbodies
* GUI
* Particle System

### Resources
* [Udemy OpenGL Course](https://www.udemy.com/course/graphics-with-modern-opengl/)
* Unity Game Development Experience for Component System Structure
* Game Engine Architecture by Jason Gregory
