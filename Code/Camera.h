#include <vector>
#include <math.h>
#include <gl/glut.h>

using namespace std;

class Camera
{
public:

	GLfloat extParameters[16]; // 4x4 matrix of ext. parameters
	Camera();
	void setView();
	void translateLoc(float x, float y, float z);
	void translateGlob(float x, float y, float z);
	void rotateLoc(float deg, float x, float y, float z);
	void rotateGlob(float deg, float x, float y, float z);
	void do_x_rotation(float deg);
	void do_y_rotation(float deg); 
	void do_z_rotation(float deg);
};

