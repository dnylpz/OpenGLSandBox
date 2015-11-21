#pragma once
#include"Transforms.h"
#include<math.h>
#include<iostream>
#define PI 3.1415926535

/*
	Esta funcion hace la de escala, recuerda que para escalar una matriz
	literalmente usas un valor escalar (casi obvio) para multiplicar todos
	los elementos de la matriz.

	aqui se usa un for dentro de otro for para multiplicar cada uno de los elementos de la matrix de 4*4

	los parametros son una referencia a tu matriz de modelo y el valor escalar.
*/
void Transforms::uniformScale(float matrix[4][4], float scaleFactor){
	float scaleMatrix[4][4] = {
		scaleFactor,0,0,0,
		0,scaleFactor,0,0,
		0,0,scaleFactor,0,
		0,0,0,1
	};
	multiplyMatrices(matrix, scaleMatrix);
	
}

/*
	Esta funcion hace la traslacion del objeto completo hacia el punto dado por el vector x,y,z

	sus parametros son tu matriz de modelo y el vector tX,tY,tZ
*/
void Transforms::uniformTranslate(float matrix[4][4], float tX, float tY, float tZ){
	float TranslationMatrix[4][4] = {
		1, 0, 0, tX,
		0, 1, 0, tY,
		0, 0, 1, tZ,
		0, 0, 0, 1
	};
	
	multiplyMatrices(matrix, TranslationMatrix);
}
/*
	Rota en un axis los parametros son la matriz el angulo y el axis
*/
void Transforms::axisRotate(float matrix[4][4], float angle, axis a){
	float xRotationMatrix[4][4] = {
		1, 0, 0, 0,
		0, cos(angle *(PI / 180)), -sin(angle*(PI / 180)), 0,
		0, sin(angle*(PI / 180)), cos(angle *(PI / 180)), 0,
		0, 0, 0, 1
	};
	float yRotationMatrix[4][4] = {
		cos(angle *(PI / 180)), 0, sin(angle*(PI / 180)), 0,
		0, 1, 0, 0,
		-sin(angle*(PI / 180)), 0, cos(angle *(PI / 180)), 0,
		0, 0, 0, 1
	};
	float zRotationMatrix[4][4] = {
		cos(angle *(PI / 180)), -sin(angle*(PI / 180)), 0, 0,
		sin(angle*(PI / 180)), cos(angle *(PI / 180)), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
	switch (a){
	case Transforms::_rX:
		multiplyMatrices(matrix, xRotationMatrix);
	
		return;
	case Transforms::_rY:
		multiplyMatrices(matrix, yRotationMatrix);
		return;
	case Transforms::_rZ:
		multiplyMatrices(matrix, zRotationMatrix);
		return;
	}

}
void Transforms::multiplyMatrices(float a[4][4], float b[4][4]){
	float c[4][4];
	float d=0;
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			for (int k = 0; k < 4; k++){
				d += a[i][k] * b[k][j];
			}
			c[i][j] = d;
			d = 0;
		}
	}
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			a[i][j] = c[i][j];
		}
	}
}