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
	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadMatrixf(extParameters);
	glRotatef(deg, x, y, z);
	glGetFloatv(GL_MODELVIEW_MATRIX, extParameters);
	glPopMatrix();

	//glMatrixMode(GL_MODELVIEW);
	//
	//// where the magic begins
	//deg /= 57.2957795f;

	//// x axis rotation

	//GLfloat x_x = x;
	//GLfloat y_x = (y * cos(deg)) + (-sin(deg)*z);
	//GLfloat z_x = (y * sin(deg)) + (cos(deg)*z);

	//GLfloat x_rotatedMatrix[16];
	//
	//memset(x_rotatedMatrix, 0, 16);

	//x_rotatedMatrix[0] = x_x;
	//x_rotatedMatrix[5] = y_x;
	//x_rotatedMatrix[10] = z_x;
	//x_rotatedMatrix[15] = 1;

	//// y axis rotation

	//GLfloat x_y = (x * cos(deg)) + (z * sin(deg));
	//GLfloat y_y = y;
	//GLfloat z_y = (-x * sin(deg)) + (z * cos(deg));

	//GLfloat y_rotatedMatrix[16];

	//memset(y_rotatedMatrix, 0, 16);

	//y_rotatedMatrix[0] = x_y;
	//y_rotatedMatrix[5] = y_y;
	//y_rotatedMatrix[10] = z_y;
	//y_rotatedMatrix[15] = 1;
	//
	//// z axis rotation

	//GLfloat x_z = (cos(deg)*x) + (-sin(deg)*y);
	//GLfloat y_z = (sin(deg)*x) + (cos(deg)*y);
	//GLfloat z_z = z;

	//GLfloat z_rotatedMatrix[16];

	//memset(z_rotatedMatrix, 0, 16);

	//z_rotatedMatrix[0] = x_z;
	//z_rotatedMatrix[5] = y_z;
	//z_rotatedMatrix[10] = z_z;
	//z_rotatedMatrix[15] = 1;

	//glPushMatrix();
	//glLoadMatrixf(x_rotatedMatrix);

	//glMultMatrixf(y_rotatedMatrix);
	//glMultMatrixf(z_rotatedMatrix);

	//glGetFloatv(GL_MODELVIEW_MATRIX, extParameters);
	//glPopMatrix();
	//
}

void Camera::rotateGlob(float deg, float x, float y, float z) {

	float dx = x*extParameters[0] + y*extParameters[1] + z*extParameters[2];
	float dy = x*extParameters[4] + y*extParameters[5] + z*extParameters[6];
	float dz = x*extParameters[8] + y*extParameters[9] + z*extParameters[10];
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadMatrixf(extParameters);
	glRotatef(deg, dx, dy, dz);
	glGetFloatv(GL_MODELVIEW_MATRIX, extParameters);
	glPopMatrix();
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


