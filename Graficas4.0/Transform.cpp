#pragma once
#include "Transform.h"
#include <glm\glm.hpp>

using namespace glm;

//Parameter will scale all axis on the figure.
void Transform::scale(float uniformTransform, mat4 &toTransform){
	float x = uniformTransform;
	mat4 scalingMatrix(
		x, 0, 0, 0,
		0, x, 0, 0,
		0, 0, x, 0,
		0, 0, 0, 1
		); 
	mat4 scaledMatrix = multiplyMatrices(toTransform, scalingMatrix);
	toTransform = scaledMatrix;
}

mat4 Transform::multiplyMatrices(mat4 &toMul, mat4 &byMul){
	mat4 result(0);
	float x[4];
	float y = 0;
	for (int i = 0; i <= 3; i++) {
		for (int j = 0; j <= 3; j++) {
			for (int k = 0; k <= 3; k++) {
				x[k] = toMul[i][k] * byMul[k][j];
			}
			for (int l = 0; l <= 3; l++) {
				y += x[l];
			}
			result[i][j] = y;
			y = 0;
		}
	}
	return result;
}