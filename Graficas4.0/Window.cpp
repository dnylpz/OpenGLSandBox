#pragma once
#include<iostream>
#include"Window.h"
#include"WindowException.h"

Window::Window(){
}

Window::Window(GLuint width, GLuint height){
	this->width = width;
	this->height = height;

	if (glfwInit()){
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
		this->window = glfwCreateWindow(this->width, this->height, "Survive", nullptr, nullptr);
		if (this->window == nullptr){
			std::cout << "Failed to create window!"<<std::endl;
			glfwTerminate();
			throw windowException;
		}
		glfwMakeContextCurrent(this->window);

		glewExperimental = GL_TRUE;
		if (glewInit != GLEW_OK){
			std::cout << "Failed to initiate GLEW!" << std::endl;
			throw windowException;
		}
		glViewport(0, 0, this->width, this->height);
	}
	else{
		throw windowException;
	}
}