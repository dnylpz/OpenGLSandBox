#include<math.h>
typedef struct mat4{
	float x[4], y[4], z[4], m[4];

};

class transforms{
public:
	enum axis{
		_rX,
		_rY,
		_rZ
	};
	static float* uniformScale(float *matrix, float scaleFactor);
	static float* axisScale(float *matrix, float xScaleFactor, float yScaleFactor, float zScaleFactor);
	static float* uniformTranslate(float *matrix, float tX, float tY, float tZ);
	static float* axisRotate(float *matrix, float angle, axis a);
};