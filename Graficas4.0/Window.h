#pragma once
#define GLEW_STATIC
#include<gl\glew.h>
#include<GLFW\glfw3.h>


class Window {
public:
	Window();
	Window(GLuint height, GLuint width);
	~Window();

	GLuint height;
	GLuint width;
	bool fullscreen;
	GLFWwindow* window;

};