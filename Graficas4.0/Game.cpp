#pragma once
#include"Game.h"
#include"Window.h"
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<stdio.h>
#include"Transform.h"
#include<glm\glm.hpp>
#include<glm\gtx\transform.hpp>

void key_callback(GLFWwindow*, int, int, int, int);

//constructors
Game::Game(){

	this->window = initializeWindow(800,600);
	glfwSetKeyCallback(this->window, key_callback);

}
Game::Game(int width, int height){
	this->window = initializeWindow(width,height);
	glfwSetKeyCallback(this->window, key_callback);
#pragma region triangle_Data
	glm::mat3 triangleVertices(
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
		);
	glGenVertexArrays(1, &this->triangleVAO);
	glBindVertexArray(this->triangleVAO);
	GLuint triangleVBO;
	glGenBuffers(1, &triangleVBO);
	glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), &triangleVertices, GL_STATIC_DRAW);
	GLuint triangleVertexShader = compileShader("VertexShader.glsl", GL_VERTEX_SHADER);
	GLuint triangleFragmentShader = compileShader("FragmentShader.glsl",GL_FRAGMENT_SHADER);
	this->triangleShaderProgram = linkShader(triangleVertexShader,triangleFragmentShader);
	glDeleteShader(triangleVertexShader);
	glDeleteShader(triangleFragmentShader);
#pragma endregion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLAT), (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
}

//app cycle
void Game::run(){
	while (!glfwWindowShouldClose(this->window)){

		//check events
		glfwPollEvents();

		/////////////////
		//render stuff
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(this->triangleShaderProgram);
		glBindVertexArray(this->triangleVAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		/////////////////
		//swap buffers
		glfwSwapBuffers(this->window);
	}
	glfwTerminate();
}


//program callbacks
void key_callback(GLFWwindow* wind, int key, int scancode, int action, int mode){

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
		glfwSetWindowShouldClose(wind, GL_TRUE);
	}
}



//utility functions.
GLFWwindow* Game::initializeWindow(int width,int height){
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* wind = glfwCreateWindow(width, height, "Survive",NULL , nullptr); //change to glfwGetPrimaryMonitor to fullscreen;
	if (wind == nullptr){
		glfwTerminate();
		return nullptr;
	}
	if (wind == nullptr){
		std::cout << "Failed to create window";
	}
	glfwMakeContextCurrent(wind);
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK){
		std::cout << "something went Wrong";
	}
	glViewport(0, 0, width, height);
	return wind;
}



/*-----------------------------------------------

Name:	compile

Params:	sFile - path to a file
a_iType - type of shader (fragment, vertex, geometry)

Result:	Loads and compiles shader.

---------------------------------------------*/
GLuint Game::compileShader(char* path, int shader_mode){
	GLuint shaderID;
	FILE *fp;
	fopen_s(&fp, path, "rt");
	if (!fp) return false;
	printf("reading shader %s\n", path);
	//get all lines from file

	std::vector<std::string> sLines;
	char sLine[255];
	while (fgets(sLine, 255, fp))sLines.push_back(sLine);
	fclose(fp);

	const char** sProgram = new const char*[(int)sLines.size()];
	for (int i = 0; i < (int)sLines.size(); i++){
		sProgram[i] = sLines[i].c_str();
	}
	
	shaderID = glCreateShader(shader_mode);

	glShaderSource(shaderID, (int)sLines.size(), sProgram, NULL);
	glCompileShader(shaderID);

	delete[] sProgram;
	
	int iCompilationStatus;
	int infoLogLength;

	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &iCompilationStatus);

		
	glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
	std::vector<char> shaderErrorMessage(infoLogLength);
	glGetShaderInfoLog(shaderID, infoLogLength, NULL, &shaderErrorMessage[0]);
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	if (iCompilationStatus == GL_FALSE) return false;
	return shaderID;
}

/*-----------------------------------------------

Name:	linkProgram

Params:	vertexShader - pointer to VS
fragmentShader - pointer to FS

Result:	links the shaders

---------------------------------------------*/
GLuint Game::linkShader(GLuint vertexShader, GLuint fragmentShader){
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	return shaderProgram;
	GLint success;
	GLchar infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER LINKING FAILED" << infoLog;
	}
}

