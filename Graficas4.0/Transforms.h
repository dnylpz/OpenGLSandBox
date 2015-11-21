#pragma once
#include<math.h>

class Transforms{
public:
	static enum axis{
		_rX,
		_rY,
		_rZ
	};
	static void uniformScale(float matrix[4][4], float scaleFactor);
	static void axisScale(float matrix[4][4], float xScaleFactor, float yScaleFactor, float zScaleFactor);
	static void uniformTranslate(float matrix[4][4], float tX, float tY, float tZ);
	static void axisRotate(float matrix[4][4], float angle, axis a);
	static void multiplyMatrices(float a[4][4], float b[4][4]);
};