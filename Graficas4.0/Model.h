#ifndef MODEL_H
#define MODEL_H

#include"Mesh.h"
#include<vector>
#include<string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>
#include <SOIL\SOIL.h>
class Model
{
public:	
	Model(GLchar* path);
	void Draw(Shader shader);
private:
	/*Model Data*/
	vector<Mesh> meshes;
	string directory;
	vector<Texture> textures_loaded;
	void loadModel(string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type,
		string typeName);
	GLuint textureFromFile(const GLchar* path, string directory);

};
#endif