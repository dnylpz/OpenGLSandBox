#pragma once
#include<GL\glew.h>
#include<GLFW\glfw3.h>
#include<glm\glm.hpp>

using namespace glm;
class Game{
public:
	//constructors
	Game();
	~Game();


	//params//objects/variables
	GLFWwindow* window;
	GLuint triangleShaderProgram;
	GLuint triangleVAO;
	float modelMatrix[4][4];
	float projectionMatrix[4][4];
	float viewMatrix[4][4];

	
	//functions
	void run();
	GLFWwindow* initializeWindow();
	GLuint compileShader(char*, int);
	GLuint linkShader(GLuint, GLuint);

};