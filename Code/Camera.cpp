#include "Camera.h"

Camera::Camera()
{
	for (int i = 0; i < 16; i++){
		extParameters[i] = 0;
	}
	extParameters[0] = 1;
	extParameters[5] = 1;
	extParameters[10] = 1;
	extParameters[15] = 1;
}

void Camera::translateLoc(float x, float y, float z)
{
	float dx = extParameters[0] * x + extParameters[4] * y + extParameters[8] * z;
	float dy = extParameters[1] * x + extParameters[5] * y + extParameters[9] * z;
	float dz = extParameters[2] * x + extParameters[6] * y + extParameters[10] * z;

	extParameters[12] += dx;
	extParameters[13] += dy;
	extParameters[14] += dz;

}

void Camera::translateGlob(float x, float y, float z) {
	extParameters[12] += x;
	extParameters[13] += y;
	extParameters[14] += z;
}

void do_x_rotation(float deg){
	deg /= 57.2957795f; // transforms to rad so that we can use the sin and cos functions
}


