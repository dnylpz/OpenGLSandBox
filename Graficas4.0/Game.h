#pragma once
#include<GL\glew.h>
#include<GLFW\glfw3.h>
#include<glm\glm.hpp>

using namespace glm;
class Game{
public:
	//constructors
	Game();
	Game(int, int);
	~Game();


	//params//objects/variables
	GLFWwindow* window;
	GLuint triangleShaderProgram;
	GLuint triangleVAO;
	mat4 modelMatrix;
	mat4 projectionMatrix;
	mat4 viewMatrix;

	
	//functions
	void run();
	GLFWwindow* initializeWindow(int,int);
	GLuint compileShader(char*, int);
	GLuint linkShader(GLuint, GLuint);

};