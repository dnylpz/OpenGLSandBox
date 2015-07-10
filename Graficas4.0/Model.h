#pragma once
#include"GL\glew.h"
#include"GLFW\glfw3.h"
#include"glm\glm.hpp"
#include<vector>

class Model{
public:
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uv;
	std::vector<glm::vec3> normals;
	std::vector<unsigned short> indices;
	

	//pointers to gpu
	GLuint  VBO;
};