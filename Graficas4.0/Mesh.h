#pragma once
#include<GL\glew.h>
#define GLEW_STATIC
#include<GLFW\glfw3.h>
#include<string>
#include<cstring>
#include<vector>
#include"Shader.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/glm.hpp>

using namespace std;
/*
	Estructura de un vertice.
	todo vertice tiene un vector de posicion (X,Y,Z),
	sus normales para cada posicion y las coordenadas de la textura (x,y. Recuerda que las coordinadas son donde se posiciona el
	vertice sobre la textura, no viceversa).
*/
struct Vertex{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct Texture{
	GLuint id;
	string type;
	aiString path;
};


class Mesh{
public:
	
	/*
		Los indices son para que los vertices que se sobreponen no se dupliquen.
	*/
	//data
	vector<Vertex> vertices;
	vector<GLuint> indices;
	vector<Texture> textures;

	//functions.
	Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> textures);
	void Draw(Shader shader);
private:
	/* Render DATA*/
	GLuint VAO, VBO, EBO;

	void setupMesh();

};