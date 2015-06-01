#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

struct Vector
{
	float x;
	float y;
	float z;
};

struct Face
{
	vector < int > vertices ;
};

struct Texture
{
	float x;
	float y;
};

class Model
{
public:
	bool hasTexture;
	bool hasNormal;
	vector<Vector> vertices;
	vector<Face> faces;
	vector<Vector> normais;
	vector<Texture> textura;
	Model( const char* filename);
	void LoadObj(const char* filename);
	void LoadNurb(const char* filename);
	
};