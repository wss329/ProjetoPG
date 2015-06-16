#include <iostream>
#include <vector>
#include <math.h>
#include <gl/glut.h>
#include "Camera.h"


using namespace std;

struct Vector
{
	float x;
	float y;
	float z;
};


struct Face
{
	vector < int > vertices;
	vector < int > texturas;
	vector < int > normais;
};

struct Texture
{
	float x;
	float y;
};

class Model
{
public:
	double scale = 0.03;
	double rotate_x = 0;
	double rotate_y = 0;
	double rotate_z = 0;
	double translate_x = 0;
	double translate_y = 0;
	double translate_z = 0.5;
	string nome;
	bool hasTexture;
	bool hasNormal;
	Camera cameraPrincipal;
	vector<Vector> vertices;
	vector<Face> faces;
	vector<Vector> normais;
	vector<Texture> textura;
	Model(const char* path);
	void LoadObj(const char* path);
	void LoadNurb(const char* path);
	Vector getNormal(Vector p1, Vector p2, Vector p3);
	void DrawModel();
	void calcularNormal();
	void rotate();
};