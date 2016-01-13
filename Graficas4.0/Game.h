#pragma once

#include<GL\glew.h>
#define GLEW_STATIC
#include<GLFW\glfw3.h>
#include<glm\glm.hpp>
#include<glm\gtc\matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include"Model.h"
#include"Camera.h"
using namespace glm;
class Game{
public:
	//constructors
	Game();
	~Game();


	//params//objects/variables
	//GLuint (GL unsigned int) son punteros a locaciones de memoria del GPU (recuerda que la GPURAM y la CPURAM estan separadas)
	GLFWwindow* window;
	float modelMatrix[4][4];
	float projectionMatrix[4][4];
	float viewMatrix[4][4];

	float width, height;

	//placeHere your models
	
	//functions
	void run();
	

private:

	//private functions (almost all of them)

	GLFWwindow* initializeWindow();
};