#pragma once
#include"Controller.h"
#include<GLFW\glfw3.h>
#include<glm\glm.hpp>

using namespace glm;

void controller::getInput(GLFWwindow *window, mat4 *model, mat4 *view, mat4 *projection){
	static double lastTime = glfwGetTime();

	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);

	double xpos, ypos;
	if (glfwJoystickPresent(GLFW_JOYSTICK_1)){
		//do joystick behav

	}
	else{
		//joystick not pressent if it was pressent ask for it or use keyboard.

	}
}
