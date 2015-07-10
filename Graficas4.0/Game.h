#pragma once
#include<GL\glew.h>
#include<GLFW\glfw3.h>


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
	

	
	//functions
	void run();
	GLFWwindow* initializeWindow(int,int);
	GLuint compileShader(char*, int);
	GLuint linkShader(GLuint, GLuint);


};