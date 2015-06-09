#include <vector>
#include <math.h>
#include <gl/glut.h>

using namespace std;

struct Vector{
	float x;
	float y;
	float z;
	float w;
};

class Camera
{
public:

	float x_coordinate;
	float y_coordinate;
	float z_coordinate;
	Vector cameraPosition;

	void translateX(float amount);
	void translateY(float amount);
	void translateZ(float amount);
	void rotateX(float amount);
	void rotateY(float amount);
	void rotateZ(float amount);
	Camera();
};

