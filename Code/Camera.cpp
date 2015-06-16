#include "Camera.h"

int degree1, degree2, degree3;

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

void Camera::rotateLoc(float deg, float x, float y, float z) {
	degree1 = x;
	degree2 = y;
	degree3 = z;
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadMatrixf(extParameters);
	glRotatef(deg, x, y, z);
	glGetFloatv(GL_MODELVIEW_MATRIX, extParameters);
	glPopMatrix();
}

void Camera::rotateGlob(float deg, float x, float y, float z){
	//convertendo pra global
	float dx = x*extParameters[0] + y*extParameters[1] + z*extParameters[2];
	float dy = x*extParameters[4] + y*extParameters[5] + z*extParameters[6];
	float dz = x*extParameters[8] + y*extParameters[9] + z*extParameters[10];
	degree1 = dx;
	degree2 = dy;
	degree3 = dz;
	//rotacionando
	rotateLoc(deg, dx, dy, dz);
}

void Camera::setView() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	float viewmatrix[16] = {//Remove the three - for non-inverted z-axis
		extParameters[0], extParameters[4], -extParameters[8], 0,
		extParameters[1], extParameters[5], -extParameters[9], 0,
		extParameters[2], extParameters[6], -extParameters[10], 0,

		-(extParameters[0] * extParameters[12] +
		extParameters[1] * extParameters[13] +
		extParameters[2] * extParameters[14]),

		-(extParameters[4] * extParameters[12] +
		extParameters[5] * extParameters[13] +
		extParameters[6] * extParameters[14]),

		//add a - like above for non-inverted z-axis
		(extParameters[8] * extParameters[12] +
		extParameters[9] * extParameters[13] +
		extParameters[10] * extParameters[14]), 1 };
	glLoadMatrixf(viewmatrix);
}


