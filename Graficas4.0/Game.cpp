#pragma once
#include"Game.h"
#include"Window.h"
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<stdio.h>
#include"Model.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void Do_Movement();


bool keys[1024];
Camera cam(vec3(0.0f,0.0f,3.0f));

GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;


/*
	this constructor initializes the game with it's properties,
	initializes a window, sets some callbacks,
	and initializes the triangle shown in the window.
*/
Game::Game(){

	//this initializes the window
	this->window = initializeWindow();
	glfwSetKeyCallback(this->window, key_callback);
	glfwSetCursorPosCallback(this->window, mouse_callback);

}

Game::~Game(){
	glfwDestroyWindow(this->window);
}
//app cycle
void Game::run(){
	
	//Shaders here
	Shader model("VertexShader.glsl", "FragmentShader.glsl");
	//Models here
	Model nano("models/nanosuit/nanosuit.obj");

	//game loop
	while (!glfwWindowShouldClose(this->window)){

		//check events
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Check and call events
		glfwPollEvents();
		Do_Movement();

		glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		model.Use();

		//matrices
		glm::mat4 projection = glm::perspective(cam.Zoom, this->width/this->height, 0.1f, 100.0f);
		glm::mat4 view = cam.GetViewMatrix();
		glUniformMatrix4fv(glGetUniformLocation(model.Program, "projection"),
			1,GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(glGetUniformLocation(model.Program, "view"), 1,
			GL_FALSE, glm::value_ptr(view));

		//Draw the loaded model;

		glm::mat4 mod;
		mod = glm::translate(mod, glm::vec3(0.0f, -1.75f, 0.0f));
		mod = glm::scale(mod, glm::vec3(0.2f, 0.2f, 0.2f));
		glUniformMatrix4fv(glGetUniformLocation(model.Program, "model"),
			1, GL_FALSE, glm::value_ptr(mod));
		nano.Draw(model);

		/////////////////
		//swap buffers
		glfwSwapBuffers(this->window);
	}
	glfwTerminate();
}


//program callbacks for keyboard
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode){
	//cout << key << endl;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (action == GLFW_PRESS)
		keys[key] = true;
	else if (action == GLFW_RELEASE)
		keys[key] = false;
}



/*
	utility functions.
	those are utilities that are used throught the app
*/


/*
	here initializes the windows and all it's parameters;
*/

GLFWwindow* Game::initializeWindow(){
	glfwInit();
	GLFWmonitor* mMon = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(mMon);
	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	this->width = mode->width;
	this->height = mode->height;

	GLFWwindow* wind = glfwCreateWindow(mode->width, mode->height, "Survive", NULL , nullptr); //change to glfwGetPrimaryMonitor to fullscreen;
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
	glViewport(0, 0, mode->width, mode->height);
	glEnable(GL_DEPTH_TEST);
	return wind;
}





void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos;  // Reversed since y-coordinates go from bottom to left

	lastX = xpos;
	lastY = ypos;

	cam.ProcessMouseMovement(xoffset, yoffset);
}


void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	cam.ProcessMouseScroll(yoffset);
}

void Do_Movement()
{
	// Camera controls
	if (keys[GLFW_KEY_W])
		cam.ProcessKeyboard(FORWARD, deltaTime);
	if (keys[GLFW_KEY_S])
		cam.ProcessKeyboard(BACKWARD, deltaTime);
	if (keys[GLFW_KEY_A])
		cam.ProcessKeyboard(LEFT, deltaTime);
	if (keys[GLFW_KEY_D])
		cam.ProcessKeyboard(RIGHT, deltaTime);
}