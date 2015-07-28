#pragma once
#include<math.h>
#include<glm\glm.hpp>
using namespace glm;
class Transform {
public:
	static void scale(float, mat4&);
	static void scale(float, float, float, mat4&);
	static void translate(float, float, float, mat4&);
	static void rotate(float, float, float, float, mat4&);
private:
	static mat4 multiplyMatrices(mat4&, mat4&);
};