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

void Camera::rotateLoc(GLfloat deg, float x, float y, float z) {
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glLoadMatrixf(extParameters);

	//float tempx;
	//float tempy;
	//float tempz;

	//tempx = extParameters[9] * z - extParameters[10] * y;
	//tempy = extParameters[10] * x - extParameters[8] * z;
	//tempz = extParameters[8] * y - extParameters[9] * x;
	//
	//x = tempx;
	//y = tempy;
	//z = tempz;

	//x = -x;

	y = -y;

	const GLfloat ROTATE_NORMALIZER = 3.14159265358979323846 / 180;
	GLfloat sinT = sin(deg * ROTATE_NORMALIZER);
	GLfloat cosT = cos(deg * ROTATE_NORMALIZER);

	GLfloat* r = (GLfloat*)malloc(sizeof(GLfloat)* 16);

	r[0] = (cosT + (pow(x, 2) * (1 - cosT)));
	r[1] = (x * y * (1 - cosT) - (z * sinT));
	r[2] = (y * sinT) + (x * z * (1 - cosT));
	r[3] = 0;

	r[4] = ((z * sinT) + (x * y * (1 - cosT)));
	r[5] = (cosT + (pow(y, 2) * (1 - cosT)));
	r[6] = ((-x * sinT) + (y * z * (1 - cosT)));
	r[7] = 0;

	r[8] = ((-y * sinT) + (x * z * (1 - cosT)));
	r[9] = ((x * sinT) + (y * z * (1 - cosT)));
	r[10] = (cosT + (pow(z, 2) * (1 - cosT)));
	r[11] = 0;

	r[12] = 0;
	r[13] = 0;
	r[14] = 0;
	r[15] = 1;

	glMultMatrixf(r);
	glGetFloatv(GL_MODELVIEW_MATRIX, extParameters); 
}

GLfloat* createRodriguesMatrix(float x, float y, float z, GLfloat degree)
{
	const GLfloat ROTATE_NORMALIZER = 3.14159265358979323846 / 180;
	GLfloat sinT = sin(degree * ROTATE_NORMALIZER);
	GLfloat cosT = cos(degree * ROTATE_NORMALIZER);

	GLfloat* r = (GLfloat*)malloc(sizeof(GLfloat)* 16);

	r[0] = cosT + (pow(x, 2) * (1 - cosT));
	r[1] = (x * y * (1 - cosT) - (z * sinT));
	r[2] = (y * sinT) + (x * z * (1 - cosT));
	r[3] = 0;

	r[4] = (z * sinT) + (x * y * (1 - cosT));
	r[5] = cosT + (pow(y, 2) * (1 - cosT));;
	r[6] = (-x * sinT) + (y * z * (1 - cosT));
	r[7] = 0;

	r[8] = (-y * sinT) + (x * z * (1 - cosT));
	r[9] = (x * sinT) + (y * z * (1 - cosT));
	r[10] = cosT + (pow(z, 2) * (1 - cosT));;;
	r[11] = 0;

	r[12] = 0;
	r[13] = 0;
	r[14] = 0;
	r[15] = 1;

	return r;
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


